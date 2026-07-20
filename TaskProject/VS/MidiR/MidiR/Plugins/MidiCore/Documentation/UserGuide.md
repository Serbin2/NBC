# MidiCore — User Guide

A reference for the public, Blueprint-exposed API of the **MidiCore** Unreal
Engine 5.5 plugin. This guide focuses on the two classes you place in a level —
the **Midi Synth Component** (audio) and the **Midi Piano Roll Actor**
(visualization) — plus the supporting asset and Blueprint library.

For installation and quick start, see `README.md`. For third-party
licensing, see `Resources/THIRD_PARTY_NOTICES.md`. For a visual walkthrough of
how playback works internally (parse → schedule → audio-mixer pull → per-block
dispatch → synthesis → visualization sync), open `Documentation/PlaybackFlow.html`
in a browser.

> **Platform:** Windows (Win64) only. The bundled native libraries are Windows
> DLLs.

---

## Table of contents
1. [Concepts](#concepts)
2. [Midi Synth Component](#midi-synth-component)
3. [Midi Piano Roll Actor](#midi-piano-roll-actor)
4. [MIDI File Asset](#midi-file-asset)
5. [Midi Blueprint Library](#midi-blueprint-library)
6. [Common workflows](#common-workflows)
7. [Resource path resolution](#resource-path-resolution)
8. [Runtime notes & limits](#runtime-notes--limits)

---

## Concepts

- **Source of MIDI data.** Both the synth component and the piano-roll actor can
  read MIDI from either an imported **`MidiAsset`** (a `UMidiFileAsset`) or a
  **`MidiFilePath`** string. If `MidiAsset` is set, it always wins;
  `MidiFilePath` is used only when `MidiAsset` is empty.
- **Channels.** MIDI channels are `0–15`. Channel `10` (index 9) is the GM drum
  channel and is excluded from transposition.
- **Audio vs. visualization.** The synth component produces sound; the piano-roll
  actor draws notes as 3D bars. They are independent but can be combined on one
  actor so the playhead follows the audio clock (see `bSyncToSynth`).

---

## Midi Synth Component

`UMidiSynthComponent` (`MidiSynthComponent.h`) — a `USynthComponent` that
flattens parsed MIDI events and renders them with FluidSynth + a soundfont
directly on the UE audio thread.

Class group **Audio**, spawnable in Blueprints. Add it to any actor, set the MIDI
source and soundfont, then call `PlayMidi`.

### Properties

All are `EditAnywhere, BlueprintReadWrite`, category **Midi**.

| Property | Type | Default | Notes |
|---|---|---|---|
| `MidiAsset` | `UMidiFileAsset*` | none | Imported `.mid` asset. Takes priority over `MidiFilePath`. |
| `MidiFilePath` | `FString` | `"goit.mid"` | Relative paths resolve under project `Content/` (see [resolution](#resource-path-resolution)). Used only when `MidiAsset` is empty. |
| `SoundFontPath` | `FString` | `"GeneralUser-GS.sf2"` | `.sf2` soundfont. Relative paths resolve like above. |
| `Gain` | `float` | `0.2` | Master gain, clamped `0.0–1.0`. |
| `PlaybackSpeed` | `float` | `1.0` | Tempo multiplier, clamped `0.25–4.0`. |
| `Transpose` | `int32` | `0` | Semitones, clamped `-24–24`. Drum channel excluded. |
| `bLoop` | `bool` | `false` | Restart from the beginning at end of song. |
| `bAutoPlayOnBeginPlay` | `bool` | `true` | Auto-start in `BeginPlay`. |

### Playback control (Blueprint callable)

| Function | Description |
|---|---|
| `PlayMidi()` | Play from the start. |
| `StopMidi()` | Stop and reset. |
| `PauseMidi()` | Pause at the current position. |
| `ResumeMidi()` | Resume from a pause. |
| `SeekSeconds(float Seconds)` | Jump to a time, performing a MIDI "chase" so controllers/program changes are correct. |
| `SetPlaybackSpeed(float Speed)` | Change tempo multiplier (same range as the property). |
| `SetGainLevel(float InGain)` | Change master gain (`0.0–1.0`). |
| `SetTranspose(int32 Semitones)` | Transpose by `-24–24` semitones (drum channel unaffected). |
| `SetLoop(bool bInLoop)` | Enable/disable looping. |
| `SetChannelMute(int32 Channel, bool bMute)` | Mute/unmute a channel (`0–15`). Muting silences sounding notes immediately and blocks new note-ons. |
| `ToggleChannelMute(int32 Channel)` | Flip the mute state of a channel. |

### Editor preview (Details-panel buttons)

These run in the editor **without entering PIE** — handy for auditioning a setup:

| Function | Description |
|---|---|
| `PreviewPlay()` | Play in the editor world. |
| `PreviewStop()` | Stop the editor preview. |

### Queries (Blueprint pure)

| Function | Returns | Description |
|---|---|---|
| `GetPlayPositionSeconds()` | `float` | Current playback position, in seconds. Used to sync visualization. |
| `GetDurationSeconds()` | `float` | Total song length, in seconds. |
| `IsPlayingMidi()` | `bool` | `true` while playing (not stopped). |
| `IsChannelMuted(int32 Channel)` | `bool` | Mute state of a channel. |

> **Threading.** Control calls come from the game thread and are handed to the
> audio render thread via atomics, so they are safe to call any time after the
> component is active. Each component owns its own FluidSynth instance and
> soundfont (see [Runtime notes](#runtime-notes--limits)).

---

## Midi Piano Roll Actor

`AMidiPianoRollActor` (`MidiPianoRollActor.h`) — parses a MIDI file and lays its
notes out as 3D bars:

- **X axis** = time (bar position = start second, length = duration)
- **Z axis** = pitch (`0–127`)
- **Color** = channel
- A vertical **playhead** sweeps the time axis during playback.

Notes are added as instances to per-channel `UInstancedStaticMeshComponent`s, so
even large files stay cheap. Dropping the actor into a level builds the bars
immediately in `OnConstruction`.

### Properties

All are `EditAnywhere, BlueprintReadWrite`, category **Midi**.

| Property | Type | Default | Notes |
|---|---|---|---|
| `MidiAsset` | `UMidiFileAsset*` | none | Imported `.mid` asset. Takes priority over `MidiFilePath`. |
| `MidiFilePath` | `FString` | `"goit.mid"` | Relative paths resolve like the synth component. Used only when `MidiAsset` is empty. |
| `TimeScale` | `float` | `100` | World units per second (horizontal scale). |
| `PitchScale` | `float` | `15` | World units per semitone (vertical scale). |
| `NoteHeight` | `float` | `10` | Bar thickness along Z (uu). |
| `NoteDepth` | `float` | `8` | Bar depth along Y (uu). |
| `bAnimatePlayhead` | `bool` | `true` | Move the playhead automatically during play. |
| `PlaybackSpeed` | `float` | `1` | Playhead speed — **only** used when sync is off or there is no synth component. |
| `bSyncToSynth` | `bool` | `true` | Lock the playhead to a Midi Synth Component on the **same actor** (removes audio/visual drift). Falls back to `PlaybackSpeed` if no component is found. |
| `PlaybackOffsetSeconds` | `float` | `0` | Fine playhead offset (seconds). Positive = playhead leads the audio; negative = lags. |

### Functions

| Function | Description |
|---|---|
| `Rebuild()` | Re-parse the source and redraw all bars. Available as a Details-panel button and Blueprint callable. Call it after changing the asset/path or layout scales. |

---

## MIDI File Asset

`UMidiFileAsset` (`MidiFileAsset.h`) — a `BlueprintType` container that holds the
raw bytes of a Standard MIDI File plus display metadata.

**Importing:** drag a `.mid` / `.midi` file into the Content Browser. The editor
module's factory creates a `UMidiFileAsset`, stores the bytes, and fills in the
metadata. Right-click the asset for **Play / Stop** preview.

| Member | Type | Description |
|---|---|---|
| `RawData` | `TArray<uint8>` | Raw `.mid` bytes, passed straight to the parser at runtime. |
| `Format` | `int32` | SMF format (0/1/2). Read-only. |
| `TrackCount` | `int32` | Number of tracks. Read-only. |
| `EventCount` | `int32` | Total MIDI events. Read-only. |
| `NoteCount` | `int32` | Total note segments. Read-only. |
| `DurationSeconds` | `float` | Song length in seconds. Read-only. |
| `SourceFilePath` | `FString` | Original import path (informational). Read-only. |
| `RefreshInfo()` | — | Re-parse `RawData` and recompute the metadata above. Called automatically on import. |

---

## Midi Blueprint Library

`UMidiBlueprintLibrary` (`MidiBlueprintLibrary.h`) — static helpers to parse MIDI
without a component, e.g. for custom visualizers or tools.

| Function | Display name | Description |
|---|---|---|
| `LoadMidiInfo(FilePath, OutFormat, OutTrackCount, OutEventCount, OutNoteCount, OutDurationSeconds)` → `bool` | **Load MIDI Info** | Parse a `.mid` path and return summary counts and duration. Returns `true` on success. |
| `LoadMidiNotes(FilePath, OutNotes)` → `bool` | **Load MIDI Notes** | Parse a `.mid` path and return every note segment. |
| `LoadMidiNotesFromAsset(Asset, OutNotes)` → `bool` | **Load MIDI Notes (Asset)** | Same, but from an imported `UMidiFileAsset`. |

`ResolveMidiResourcePath(In, PluginSubDir)` is a C++-only static helper
(not Blueprint) used internally to resolve relative resource paths — see
[Resource path resolution](#resource-path-resolution).

### `FMidiNoteSegment`

The note struct returned by the library (one piano-roll rectangle):

| Field | Type | Range | Meaning |
|---|---|---|---|
| `Channel` | `int32` | `0–15` | MIDI channel. |
| `Note` | `int32` | `0–127` | Pitch. |
| `Velocity` | `int32` | `0–127` | Note-on velocity. |
| `StartSeconds` | `float` | — | Start time. |
| `EndSeconds` | `float` | — | End time. |

---

## Common workflows

**Audio only**
1. Add a **Midi Synth Component** to an actor.
2. Set `MidiAsset` (or leave `MidiFilePath` at the default).
3. Leave `bAutoPlayOnBeginPlay = true`, or call `PlayMidi` from Blueprint.

**Visualization only**
1. Drop an **AMidiPianoRollActor** into the level.
2. Point `MidiAsset` / `MidiFilePath` at your file. Bars appear immediately.
3. Tune `TimeScale` / `PitchScale` and press **Rebuild** if you change them.

**Synced audio + visualization (recommended)**
1. Add **both** a Midi Synth Component and use an **AMidiPianoRollActor** for the
   same content.
2. Attach the Midi Synth Component to the **same actor** as the piano roll.
3. Keep `bSyncToSynth = true` — the playhead now follows
   `GetPlayPositionSeconds()`, so audio and visuals never drift.
4. Use `PlaybackOffsetSeconds` for fine alignment if needed.

---

## Resource path resolution

Relative `SoundFontPath` / `MidiFilePath` (and the library's path functions)
resolve in this order:

1. `<Project>/Content/<path>` — lets a project override the bundled defaults.
2. `<Plugin>/Content/SoundFonts|Midi/<filename>` — the bundled fallback.

Absolute paths are used as-is. If nothing is found, the project path is returned
and a load failure is logged. This is why the plugin plays out of the box, yet
you can drop your own `.sf2` into the project's `Content/` to override it.

---

## Runtime notes & limits

- **Independent instances.** Each `UMidiSynthComponent` owns its own FluidSynth
  instance and loads its **own copy of the soundfont** (~30 MB for the bundled
  one). There is no shared mutable state between components.
- **Multiple simultaneous playback** is supported and safe — you can place
  several synth components and play different files at once. The cost scales with
  count:
  - **Memory:** N components ≈ N × soundfont size.
  - **Startup:** the soundfont is loaded (blocking) on the game thread when a
    component starts; starting many at once can cause a hitch.
  - **CPU/audio:** each instance synthesizes every audio block, so DSP cost and
    voice count grow with N.
- **Editor preview is single-instance by design.** The right-click asset preview
  and the component's `PreviewPlay` use one shared editor-preview slot, so a new
  preview stops the previous one. This limit applies to editor preview only — not
  to runtime components.
- **Lifetime.** Audio render and game-thread teardown are serialized internally,
  so destroying an actor mid-playback (or shutting down the editor) is safe.
