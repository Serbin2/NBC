// Markdown.cpp : 간단한 마크다운 -> RTF 변환기
//
// RichEdit 컨트롤은 EM_STREAMIN(SF_RTF) 메시지로 RTF 텍스트를 받아
// 서식을 그려줍니다. 이 파일은 마크다운 문법을 해석해 그에 맞는 RTF를
// 생성합니다. 비ASCII 문자(한글 등)는 \uN? 형태로 인코딩합니다.

#include "Markdown.h"

#include <string>
#include <vector>

namespace {

// 영문/숫자/밑줄/CJK 등 "단어 문자" 여부 (밑줄 강조의 단어 내부 판별용)
bool IsWordCh(wchar_t c) {
    return (c >= L'0' && c <= L'9') ||
           (c >= L'A' && c <= L'Z') ||
           (c >= L'a' && c <= L'z') ||
           c == L'_' || c >= 128;
}

// 한 문자를 RTF로 안전하게 추가 (특수문자 이스케이프 + 유니코드 인코딩)
void AppendChar(std::string& out, wchar_t c) {
    switch (c) {
    case L'\\': out += "\\\\"; break;
    case L'{':  out += "\\{";  break;
    case L'}':  out += "\\}";  break;
    case L'\t': out += "\\tab "; break;
    default:
        if (c >= 0x20 && c < 0x7F) {
            out += static_cast<char>(c);
        } else {
            // RTF \u 제어어는 부호 있는 16비트 값을 사용한다.
            int v = static_cast<int>(static_cast<unsigned short>(c));
            if (v >= 0x8000) v -= 0x10000;
            out += "\\u";
            out += std::to_string(v);
            out += '?';
        }
    }
}

void AppendText(std::string& out, const std::wstring& s, size_t a, size_t b) {
    for (size_t i = a; i < b; ++i) AppendChar(out, s[i]);
}
void AppendTextAll(std::string& out, const std::wstring& s) {
    AppendText(out, s, 0, s.size());
}

// 위치 i 에서 시작하는 문자 c 의 연속 개수
size_t RunLen(const std::wstring& s, size_t i, wchar_t c) {
    size_t n = 0;
    while (i + n < s.size() && s[i + n] == c) ++n;
    return n;
}

// 인라인 코드(백틱)의 닫는 위치: 정확히 같은 개수의 백틱
size_t FindCodeClose(const std::wstring& s, size_t from, size_t ticks) {
    size_t j = from;
    while (j < s.size()) {
        if (s[j] == L'`') {
            size_t r = RunLen(s, j, L'`');
            if (r == ticks) return j;
            j += r;
        } else {
            ++j;
        }
    }
    return std::wstring::npos;
}

// 강조(*, _)의 닫는 위치: want 개수 이상인 같은 문자의 런
size_t FindEmClose(const std::wstring& s, size_t from, wchar_t c, size_t want) {
    size_t j = from;
    while (j < s.size()) {
        if (s[j] == L'\\') { j += 2; continue; }
        if (s[j] == c) {
            size_t r = RunLen(s, j, c);
            if (r >= want) return j;
            j += r;
        } else {
            ++j;
        }
    }
    return std::wstring::npos;
}

void AppendInline(std::string& out, const std::wstring& s);

// {tags 텍스트} 형태의 그룹을 출력. 그룹이 닫히면 서식이 자동 복원된다.
void EmitStyled(std::string& out, const char* tags, const std::wstring& text) {
    out += '{';
    out += tags;
    out += ' ';
    AppendTextAll(out, text);
    out += '}';
}

// 한 줄(또는 텍스트 조각)의 인라인 마크다운을 RTF로 변환
void AppendInline(std::string& out, const std::wstring& s) {
    size_t n = s.size(), i = 0, lit = 0;
    auto flushLit = [&](size_t end) { if (end > lit) AppendText(out, s, lit, end); };

    while (i < n) {
        wchar_t c = s[i];
        bool handled = false;

        if (c == L'\\' && i + 1 < n) {
            // 백슬래시 이스케이프: 다음 문자를 그대로 출력
            flushLit(i);
            AppendChar(out, s[i + 1]);
            i += 2; lit = i; handled = true;
        } else if (c == L'`') {
            // 인라인 코드
            size_t ticks = RunLen(s, i, L'`');
            size_t close = FindCodeClose(s, i + ticks, ticks);
            if (close != std::wstring::npos) {
                flushLit(i);
                out += "{\\f1\\fs20\\highlight4 ";
                AppendText(out, s, i + ticks, close);
                out += '}';
                i = close + ticks; lit = i; handled = true;
            } else {
                i += ticks; handled = true;  // 짝이 없으면 리터럴 백틱으로 둔다
            }
        } else if (c == L'!' && i + 1 < n && s[i + 1] == L'[') {
            // 이미지 ![alt](url)
            size_t rb = s.find(L']', i + 2);
            if (rb != std::wstring::npos && rb + 1 < n && s[rb + 1] == L'(') {
                size_t rp = s.find(L')', rb + 2);
                if (rp != std::wstring::npos) {
                    flushLit(i);
                    std::wstring alt = s.substr(i + 2, rb - (i + 2));
                    EmitStyled(out, "\\cf2\\i", L"[\xC774\xBBF8\xC9C0: " + alt + L"]");
                    i = rp + 1; lit = i; handled = true;
                }
            }
        } else if (c == L'[') {
            // 링크 [text](url)
            size_t rb = s.find(L']', i + 1);
            if (rb != std::wstring::npos && rb + 1 < n && s[rb + 1] == L'(') {
                size_t rp = s.find(L')', rb + 2);
                if (rp != std::wstring::npos) {
                    flushLit(i);
                    std::wstring text = s.substr(i + 1, rb - (i + 1));
                    EmitStyled(out, "\\cf3\\ul", text);
                    i = rp + 1; lit = i; handled = true;
                }
            }
        } else if (c == L'*' || c == L'_') {
            // 강조 (굵게/기울임)
            bool ok = true;
            if (c == L'_' && i > 0 && IsWordCh(s[i - 1])) ok = false;  // snake_case 보호
            if (ok) {
                size_t run = RunLen(s, i, c);
                size_t want = run >= 3 ? 3 : run;
                size_t close = FindEmClose(s, i + run, c, want);
                if (close != std::wstring::npos) {
                    flushLit(i);
                    const char* tags = (want >= 3) ? "\\b\\i" : (want == 2) ? "\\b" : "\\i";
                    std::wstring inner = s.substr(i + run, close - (i + run));
                    out += '{';
                    out += tags;
                    out += ' ';
                    AppendInline(out, inner);  // 중첩 서식 허용
                    out += '}';
                    i = close + want; lit = i; handled = true;
                } else {
                    i += run; handled = true;  // 짝이 없으면 리터럴
                }
            }
        }

        if (!handled) ++i;
    }
    flushLit(n);
}

std::wstring LTrim(const std::wstring& s) {
    size_t i = 0;
    while (i < s.size() && (s[i] == L' ' || s[i] == L'\t')) ++i;
    return s.substr(i);
}
std::wstring RTrim(const std::wstring& s) {
    size_t e = s.size();
    while (e > 0 && (s[e - 1] == L' ' || s[e - 1] == L'\t')) --e;
    return s.substr(0, e);
}
// 앞쪽 공백 폭(탭=4칸) 계산 및 첫 비공백 인덱스 반환
size_t LeadWidth(const std::wstring& s, size_t& idx) {
    size_t w = 0, i = 0;
    while (i < s.size() && (s[i] == L' ' || s[i] == L'\t')) { w += (s[i] == L'\t') ? 4 : 1; ++i; }
    idx = i;
    return w;
}
bool IsBlank(const std::wstring& s) {
    for (wchar_t c : s) if (c != L' ' && c != L'\t') return false;
    return true;
}

// ---- 표(GFM table) ----
enum Align { AL_LEFT, AL_CENTER, AL_RIGHT };

// 표의 한 행을 셀 목록으로 분리한다. 앞뒤 '|' 는 선택, '\|' 는 리터럴.
std::vector<std::wstring> SplitRow(const std::wstring& line) {
    std::wstring s = RTrim(LTrim(line));
    size_t start = (!s.empty() && s[0] == L'|') ? 1 : 0;
    std::vector<std::wstring> cells;
    std::wstring cur;
    for (size_t i = start; i < s.size(); ++i) {
        wchar_t c = s[i];
        if (c == L'\\' && i + 1 < s.size()) { cur += c; cur += s[i + 1]; ++i; continue; }
        if (c == L'|') { cells.push_back(RTrim(LTrim(cur))); cur.clear(); }
        else cur += c;
    }
    std::wstring last = RTrim(LTrim(cur));
    if (!last.empty() || cells.empty()) cells.push_back(last);
    return cells;
}

// 구분 행( |---|:--:|--:| )인지 검사하고 열별 정렬을 채운다.
bool ParseDelimiter(const std::wstring& line, std::vector<int>& aligns) {
    std::wstring t = RTrim(LTrim(line));
    if (t.empty()) return false;
    bool hasDash = false, hasPipe = false;
    for (wchar_t c : t) {
        if (c == L'-') hasDash = true;
        else if (c == L'|') hasPipe = true;
        else if (c == L':' || c == L' ' || c == L'\t') {}
        else return false;
    }
    if (!hasDash || !hasPipe) return false;   // 구분 행은 '-' 와 '|' 를 반드시 포함
    std::vector<std::wstring> cells = SplitRow(t);
    aligns.clear();
    for (std::wstring c : cells) {
        c = RTrim(LTrim(c));
        if (c.empty()) return false;
        for (wchar_t ch : c) if (ch != L'-' && ch != L':') return false;
        if (c.find(L'-') == std::wstring::npos) return false;
        bool left = c.front() == L':';
        bool right = c.back() == L':';
        aligns.push_back(left && right ? AL_CENTER : right ? AL_RIGHT : AL_LEFT);
    }
    return !aligns.empty();
}

// 셀 표시 폭 추정 (CJK 문자는 2칸으로 계산)
int CellWidth(const std::wstring& s) {
    int n = 0;
    for (wchar_t c : s) n += (c >= 0x1100) ? 2 : 1;
    return n;
}

// 표 하나를 RTF 표로 출력
void EmitTable(std::string& out,
               std::vector<std::wstring> header,
               const std::vector<int>& aligns,
               std::vector<std::vector<std::wstring>> rows) {
    size_t ncol = aligns.size();
    if (ncol == 0) return;
    header.resize(ncol);

    // 열 너비를 내용 길이에 비례해 배분 (셀 안에서 자동 줄바꿈됨)
    std::vector<int> wmax(ncol, 1);
    for (size_t c = 0; c < ncol; ++c) wmax[c] = CellWidth(header[c]);
    for (std::vector<std::wstring> r : rows) {
        r.resize(ncol);
        for (size_t c = 0; c < ncol; ++c) { int d = CellWidth(r[c]); if (d > wmax[c]) wmax[c] = d; }
    }
    int sum = 0; for (int x : wmax) sum += x; if (sum <= 0) sum = 1;
    const int target = 9000, minc = 900;   // 전체 약 6.25인치, 열 최소 폭
    std::vector<int> cellx(ncol);
    int acc = 0;
    for (size_t c = 0; c < ncol; ++c) {
        int w = (int)((long long)target * wmax[c] / sum);
        if (w < minc) w = minc;
        acc += w;
        cellx[c] = acc;
    }

    const std::string border =
        "\\clbrdrt\\brdrs\\brdrw10\\brdrcf6"
        "\\clbrdrl\\brdrs\\brdrw10\\brdrcf6"
        "\\clbrdrb\\brdrs\\brdrw10\\brdrcf6"
        "\\clbrdrr\\brdrs\\brdrw10\\brdrcf6";

    auto emitRow = [&](std::vector<std::wstring> cells, bool head) {
        cells.resize(ncol);
        out += "\\trowd\\trgaph108\\trleft0";
        for (size_t c = 0; c < ncol; ++c) {
            out += border;
            if (head) out += "\\clcbpat4";          // 헤더 셀 음영
            out += "\\cellx";
            out += std::to_string(cellx[c]);
        }
        out += "\n";
        for (size_t c = 0; c < ncol; ++c) {
            const char* q = aligns[c] == AL_CENTER ? "\\qc" : aligns[c] == AL_RIGHT ? "\\qr" : "\\ql";
            out += "\\pard\\intbl";
            out += q;
            out += "\\sa40\\sb40\\b0\\i0\\ul0\\highlight0\\f0\\fs22\\cf1 ";
            if (head) out += "\\b ";
            AppendInline(out, cells[c]);
            out += "\\cell ";
        }
        out += "\\row\n";
    };

    emitRow(header, true);
    for (std::vector<std::wstring>& r : rows) emitRow(r, false);
    out += "\\pard\\sa120\\sl276\\slmult1\\b0\\i0\\ul0\\highlight0\\f0\\fs22\\cf1\n";
}

} // namespace

std::string MarkdownToRtf(const std::wstring& mdRaw) {
    // 개행을 \n 으로 정규화
    std::wstring md;
    md.reserve(mdRaw.size());
    for (size_t i = 0; i < mdRaw.size(); ++i) {
        wchar_t c = mdRaw[i];
        if (c == L'\r') { md += L'\n'; if (i + 1 < mdRaw.size() && mdRaw[i + 1] == L'\n') ++i; }
        else md += c;
    }

    // 줄 단위 분리
    std::vector<std::wstring> lines;
    {
        size_t st = 0;
        for (size_t i = 0; i <= md.size(); ++i) {
            if (i == md.size() || md[i] == L'\n') { lines.push_back(md.substr(st, i - st)); st = i + 1; }
        }
    }

    std::string out;
    out.reserve(mdRaw.size() * 2 + 1024);
    // RTF 머리말: 폰트 테이블 / 색 테이블
    out += "{\\rtf1\\ansi\\ansicpg65001\\deff0\\uc1\n";
    out += "{\\fonttbl{\\f0\\fswiss Malgun Gothic;}{\\f1\\fmodern Consolas;}}\n";
    out += "{\\colortbl ;"
           "\\red36\\green41\\blue46;"     // 1 본문
           "\\red106\\green115\\blue125;"  // 2 회색(인용/이미지/H6)
           "\\red9\\green105\\blue218;"    // 3 링크 파랑
           "\\red235\\green237\\blue240;"  // 4 인라인 코드 배경
           "\\red246\\green248\\blue250;"  // 5 코드 블록 배경
           "\\red208\\green215\\blue222;"  // 6 테두리
           "}\n";
    out += "\\f0\\fs22\\cf1\n";

    std::vector<std::wstring> para, quote, code;
    bool inFence = false;
    wchar_t fenceCh = 0;
    size_t fenceLen = 0;

    auto flushPara = [&]() {
        if (para.empty()) return;
        out += "\\pard\\sa120\\sl276\\slmult1\\b0\\i0\\ul0\\highlight0\\f0\\fs22\\cf1 ";
        for (size_t k = 0; k < para.size(); ++k) { if (k) out += ' '; AppendInline(out, para[k]); }
        out += "\\par\n";
        para.clear();
    };
    auto flushQuote = [&]() {
        if (quote.empty()) return;
        out += "\\pard\\li360\\brdrl\\brdrs\\brdrw40\\brdrcf6\\sa120\\sl276\\slmult1\\b0\\ul0\\highlight0\\i\\f0\\fs22\\cf2 ";
        for (size_t k = 0; k < quote.size(); ++k) { if (k) out += ' '; AppendInline(out, quote[k]); }
        out += "\\par\n";
        quote.clear();
    };
    auto flushCode = [&]() {
        out += "\\pard\\li240\\sb60\\sa120\\b0\\i0\\ul0\\f1\\fs20\\cf1 ";
        for (size_t k = 0; k < code.size(); ++k) {
            out += "\\highlight5 ";
            AppendTextAll(out, code[k]);
            out += "\\highlight0";
            if (k + 1 < code.size()) out += "\\line\n";
        }
        out += "\\par\n";
        code.clear();
    };
    auto flushText = [&]() { flushPara(); flushQuote(); };

    for (size_t li = 0; li < lines.size(); ++li) {
        const std::wstring& line = lines[li];
        if (inFence) {
            size_t idx; (void)LeadWidth(line, idx);
            std::wstring t = line.substr(idx);
            size_t rl = RunLen(t, 0, fenceCh);
            if (rl >= fenceLen && IsBlank(t.substr(rl))) { inFence = false; flushCode(); }
            else code.push_back(line);
            continue;
        }

        // 코드 펜스 시작 (``` 또는 ~~~)
        {
            size_t idx; (void)LeadWidth(line, idx);
            std::wstring t = line.substr(idx);
            if (t.size() >= 3 && (t[0] == L'`' || t[0] == L'~') && RunLen(t, 0, t[0]) >= 3) {
                flushText();
                inFence = true; fenceCh = t[0]; fenceLen = RunLen(t, 0, t[0]); code.clear();
                continue;
            }
        }

        if (IsBlank(line)) { flushText(); continue; }

        // 제목 (#, ##, ... ######)
        {
            size_t i = 0; while (i < line.size() && line[i] == L' ') ++i;
            size_t h = 0; while (i + h < line.size() && line[i + h] == L'#') ++h;
            if (h >= 1 && h <= 6 && i + h < line.size() && line[i + h] == L' ') {
                flushText();
                std::wstring content = RTrim(line.substr(i + h + 1));
                size_t e = content.size();
                while (e > 0 && content[e - 1] == L'#') --e;      // 끝의 닫는 # 제거
                if (e < content.size()) content = RTrim(content.substr(0, e));
                const char* fs; bool border = false;
                switch (h) {
                case 1: fs = "44"; border = true; break;
                case 2: fs = "36"; border = true; break;
                case 3: fs = "30"; break;
                case 4: fs = "26"; break;
                case 5: fs = "24"; break;
                default: fs = "22"; break;
                }
                out += "\\pard\\sb240\\sa120";
                if (border) out += "\\brdrb\\brdrs\\brdrw10\\brdrcf6\\sa180";
                out += "\\b0\\i0\\ul0\\highlight0\\f0\\fs";
                out += fs;
                out += (h >= 6) ? "\\cf2" : "\\cf1";
                out += "\\b ";
                AppendInline(out, content);
                out += "\\par\n";
                continue;
            }
        }

        // 구분선 (---, ***, ___)
        {
            std::wstring t = LTrim(line);
            std::wstring cmp; for (wchar_t c : t) if (c != L' ') cmp += c;
            if (cmp.size() >= 3 &&
                (cmp == std::wstring(cmp.size(), L'-') ||
                 cmp == std::wstring(cmp.size(), L'*') ||
                 cmp == std::wstring(cmp.size(), L'_'))) {
                flushText();
                out += "\\pard\\brdrb\\brdrs\\brdrw15\\brdrcf6\\sb120\\sa120\\par\n";
                continue;
            }
        }

        // 인용문 (>)
        {
            size_t i = 0; while (i < line.size() && line[i] == L' ') ++i;
            if (i < line.size() && line[i] == L'>') {
                flushPara();
                std::wstring content = line.substr(i + 1);
                if (!content.empty() && content[0] == L' ') content = content.substr(1);
                quote.push_back(content);
                continue;
            } else {
                flushQuote();
            }
        }

        // 목록 (-, *, + / 1. 2. ...)
        {
            size_t idx; size_t w = LeadWidth(line, idx);
            std::wstring t = line.substr(idx);
            bool ul = t.size() >= 2 && (t[0] == L'-' || t[0] == L'*' || t[0] == L'+') &&
                      (t[1] == L' ' || t[1] == L'\t');
            size_t d = 0; while (d < t.size() && t[d] >= L'0' && t[d] <= L'9') ++d;
            bool ol = d >= 1 && d + 1 < t.size() && (t[d] == L'.' || t[d] == L')') &&
                      (t[d + 1] == L' ' || t[d + 1] == L'\t');
            if (ul || ol) {
                flushText();
                int level = static_cast<int>(w / 2); if (level > 5) level = 5;
                int liTw = 360 * (level + 1);
                std::wstring marker, content;
                if (ul) { marker = L"\x2022"; content = LTrim(t.substr(2)); }
                else { marker = t.substr(0, d) + L"."; content = LTrim(t.substr(d + 2)); }
                out += "\\pard\\fi-360\\li";
                out += std::to_string(liTw);
                out += "\\tx";
                out += std::to_string(liTw);
                out += "\\sa60\\sl276\\slmult1\\b0\\i0\\ul0\\highlight0\\f0\\fs22\\cf1 ";
                AppendTextAll(out, marker);
                out += "\\tab ";
                AppendInline(out, content);
                out += "\\par\n";
                continue;
            }
        }

        // 표 (GFM): 현재 줄에 '|' 가 있고 다음 줄이 구분 행이면 표로 처리
        if (line.find(L'|') != std::wstring::npos && li + 1 < lines.size()) {
            std::vector<int> aligns;
            if (ParseDelimiter(lines[li + 1], aligns)) {
                std::vector<std::wstring> header = SplitRow(line);
                std::vector<std::vector<std::wstring>> rows;
                size_t j = li + 2;
                for (; j < lines.size(); ++j) {
                    if (IsBlank(lines[j]) || lines[j].find(L'|') == std::wstring::npos) break;
                    rows.push_back(SplitRow(lines[j]));
                }
                flushText();
                EmitTable(out, header, aligns, rows);
                li = j - 1;   // 소비한 줄 다음부터 계속 (for 의 ++li 가 j 로 이동)
                continue;
            }
        }

        // 일반 문단 (연속된 줄은 한 문단으로 합쳐 부드럽게 줄바꿈)
        flushQuote();
        para.push_back(LTrim(line));
    }

    if (inFence) { inFence = false; flushCode(); }
    flushText();
    out += "}";
    return out;
}
