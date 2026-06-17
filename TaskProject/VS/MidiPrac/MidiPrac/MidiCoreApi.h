#pragma once
// ============================================================
// MidiCore DLL export/import macro.
//
//   - Building MidiCore.dll : MIDICORE_EXPORTS defined -> dllexport
//   - Consuming MidiCore.dll : (nothing defined)       -> dllimport
//   - Building as a static lib / single project: define MIDICORE_STATIC
//
// NOTE: This C++ class export model requires the DLL and every
//       consumer to be built with the SAME MSVC toolset and the SAME
//       dynamic CRT (/MD or /MDd), and matching Debug/Release. That is
//       the agreed constraint for this project.
// ============================================================
#ifdef MIDICORE_STATIC
  #define MIDICORE_API
#else
  #ifdef MIDICORE_EXPORTS
    #define MIDICORE_API __declspec(dllexport)
  #else
    #define MIDICORE_API __declspec(dllimport)
  #endif
#endif

#if defined(_MSC_VER)
  // C4251: an exported class has STL members that themselves lack a
  //        DLL interface. Safe under the same-toolset/same-CRT rule
  //        above, so silence the noise.
  #pragma warning(disable: 4251)
  // C4275: an exported class derives from a non-DLL-interface base.
  #pragma warning(disable: 4275)
#endif
