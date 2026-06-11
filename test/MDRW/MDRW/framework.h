// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ 표준 라이브러리
#include <string>
#include <vector>

// 추가 Windows 헤더 (공통 대화 상자, 셸, RichEdit)
#include <commdlg.h>
#include <shellapi.h>
#define _RICHEDIT_VER 0x0500
#include <richedit.h>

#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "shell32.lib")
