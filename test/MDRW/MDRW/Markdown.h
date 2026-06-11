#pragma once

#include <string>

// 마크다운 텍스트(UTF-16)를 RichEdit 컨트롤이 읽을 수 있는
// RTF 문자열(ASCII, 비ASCII 문자는 \uN? 로 인코딩)로 변환합니다.
std::string MarkdownToRtf(const std::wstring& markdown);
