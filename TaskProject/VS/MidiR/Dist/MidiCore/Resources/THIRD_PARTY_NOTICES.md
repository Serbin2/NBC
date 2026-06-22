# Third-Party Notices — MidiCore plugin

This plugin redistributes the following third-party components. Each remains under
its own license. The dynamic libraries below are shipped **unmodified** and are
loaded at runtime via dynamic symbol lookup (`GetProcAddress`), i.e. dynamic
linking — they are **not** statically linked into the plugin.

Binaries are located in `Binaries/Win64/` and the soundfont in
`Content/SoundFonts/`. Any of the DLLs may be replaced by the end user with a
compatible build of the same library.

---

## FluidSynth (`libfluidsynth-3.dll`)
- License: **LGPL-2.1-or-later**
- Project: https://www.fluidsynth.org/
- Source: https://github.com/FluidSynth/fluidsynth
- Notes: Used as a soundfont synthesizer. Shipped unmodified, dynamically loaded.
  Per the LGPL, you may relink/replace this library; the DLL is provided as a
  separate file in `Binaries/Win64/`.

## libsndfile (`sndfile.dll`)
- License: **LGPL-2.1-or-later**
- Project: https://libsndfile.github.io/libsndfile/
- Source: https://github.com/libsndfile/libsndfile
- Notes: Transitive dependency of FluidSynth. Shipped unmodified.

## SDL (`SDL3.dll`)
- License: **zlib License**
- Project: https://www.libsdl.org/
- Source: https://github.com/libsdl-org/SDL
- Notes: Transitive dependency of FluidSynth. Shipped unmodified.

## GeneralUser GS (`GeneralUser-GS.sf2`)
- Author: S. Christian Collins
- License: Free for distribution (see the GeneralUser GS license / README).
- Project: https://www.schristiancollins.com/generaluser.php
- Notes: Bundled as the default soundfont. You may replace it via the
  component's `SoundFontPath` property.

---

### LGPL compliance summary
FluidSynth and libsndfile are LGPL. This plugin links to them **dynamically**
(runtime `GetProcAddress`) and ships them as **separate, unmodified** DLLs, so an
end user can substitute their own compatible build. The corresponding source for
each library is available at the URLs above. For full compliance when
redistributing, include each library's full license text alongside its binary.
