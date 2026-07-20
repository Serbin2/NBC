# MidiCore

A self-contained Unreal Engine **5.5** plugin for MIDI playback and piano-roll
visualization.

- Parses Standard MIDI Files (SMF) — tracks, events, note segments.
- Synthesizes audio at runtime with **FluidSynth** + a bundled soundfont
  (no audio driver; rendered directly on the UE audio thread).
- Editor integration: import `.mid` as assets and preview them without PIE.
- 3D piano-roll actor with an audio-synced playhead.

Windows (Win64) only — the bundled native libraries are Windows DLLs.

## Install
Copy the `MidiCore` folder into your project's `Plugins/` directory and launch
the editor. The plugin ships precompiled binaries, the FluidSynth DLLs, and a
default soundfont, so **no extra setup is required**.

## Quick start
1. Add a **Midi Synth Component** to any actor.
2. Set `MidiAsset` (drag a `.mid` into the Content Browser to import) or leave
   `MidiFilePath` at the default (`goit.mid`, bundled).
3. Press **Play** (or call `PlayMidi` from Blueprint). In the editor, use the
   component's **Preview Play / Preview Stop** buttons.

To visualize, add an **AMidiPianoRollActor**, point it at the same asset/path,
and (optionally) attach a Midi Synth Component to the same actor — the playhead
follows the synth's audio clock (`bSyncToSynth`).

## Resource resolution
`SoundFontPath` / `MidiFilePath` (relative paths) resolve in this order:
1. `<Project>/Content/<path>` — lets a project override the defaults.
2. `<Plugin>/Content/SoundFonts|Midi/<filename>` — the bundled fallback.

So the plugin works out of the box, but you can drop your own `.sf2` into the
project's `Content/` to override the soundfont.

## Documentation
See `Documentation/UserGuide.md` (English) or `Documentation/UserGuide.ko.md`
(한국어) for the full Blueprint-exposed API reference — the Midi Synth Component,
the Midi Piano Roll Actor, the MIDI file asset, and the Blueprint library, with
all properties and functions.

Open `Documentation/PlaybackFlow.html` in a browser for a visual walkthrough of
how playback works end to end — MIDI parse → event schedule → the audio mixer's
pull → per-block dispatch → FluidSynth → output and visualization sync.

## Licensing
The plugin's own code is MIT (see `LICENSE`). Bundled third-party components
(FluidSynth, libsndfile, SDL, GeneralUser GS) remain under their own licenses —
see `Resources/THIRD_PARTY_NOTICES.md`. Before public distribution, set the
copyright holder in `LICENSE`.
