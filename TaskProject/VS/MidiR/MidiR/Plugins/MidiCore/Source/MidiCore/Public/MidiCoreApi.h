#pragma once
// ============================================================
// MidiCore export/import 매크로 (언리얼 모듈 / 단독 빌드 겸용)
//
//  - 언리얼 모듈로 빌드: UnrealBuildTool 이 모듈명("MidiCore")으로
//      MIDICORE_API 를 자동 정의(dllexport/dllimport)한다.
//      → 이 헤더는 이미 정의돼 있으면 건드리지 않는다(#ifndef 가드).
//  - 단독(원본 VS) 빌드: MIDICORE_EXPORTS / MIDICORE_STATIC 로 직접 정의.
//
// 같은 헤더를 두 빌드 시스템에서 그대로 쓰기 위한 구조다.
// ============================================================
#ifndef MIDICORE_API
  #ifdef MIDICORE_STATIC
    #define MIDICORE_API
  #else
    #ifdef MIDICORE_EXPORTS
      #define MIDICORE_API __declspec(dllexport)
    #else
      #define MIDICORE_API __declspec(dllimport)
    #endif
  #endif
#endif

#if defined(_MSC_VER)
  // C4251: 내보낸 클래스의 STL 멤버가 DLL 인터페이스를 갖지 않음.
  // C4275: 내보낸 클래스가 비 DLL 인터페이스 기반 클래스를 상속.
  //        동일 툴셋/CRT 규칙 아래서는 안전하므로 잡음만 끈다.
  #pragma warning(disable: 4251)
  #pragma warning(disable: 4275)
#endif
