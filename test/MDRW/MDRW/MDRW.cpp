// MDRW.cpp : 마크다운 리더 / 에디터 애플리케이션의 진입점입니다.
//
// 읽기 모드 : 마크다운을 RTF로 변환해 RichEdit 컨트롤에 서식대로 그립니다.
// 편집 모드 : 같은 컨트롤을 평문(Consolas) 모드로 바꿔 메모장처럼 편집합니다.

#include "framework.h"
#include "MDRW.h"
#include "Markdown.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 애플리케이션 상태
enum class Mode { Read, Edit };

static HWND     g_hWndMain = nullptr;   // 주 창
static HWND     g_hEdit    = nullptr;   // RichEdit 컨트롤
static HMODULE  g_richLib  = nullptr;   // Msftedit.dll 핸들
static HACCEL   g_hAccel   = nullptr;   // 단축키 테이블
static Mode     g_mode     = Mode::Read;
static std::wstring g_filePath;         // 현재 파일 경로(비어 있으면 새 문서)
static std::wstring g_markdown;         // 문서 원본(개행은 \n 으로 정규화)
static bool     g_dirty    = false;     // 저장되지 않은 변경 여부
static bool     g_suppress = false;     // 프로그램에 의한 변경 시 EN_CHANGE 무시

// 함수 선언:
ATOM             MyRegisterClass(HINSTANCE hInstance);
BOOL             InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// ===================== 유틸리티 =====================

static std::wstring Utf8ToW(const std::string& s) {
    if (s.empty()) return L"";
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), &w[0], n);
    return w;
}
static std::string WToUtf8(const std::wstring& w) {
    if (w.empty()) return std::string();
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), &s[0], n, nullptr, nullptr);
    return s;
}

// 개행을 \n 으로 정규화
static std::wstring NormalizeNewlines(const std::wstring& in) {
    std::wstring out; out.reserve(in.size());
    for (size_t i = 0; i < in.size(); ++i) {
        wchar_t c = in[i];
        if (c == L'\r') { out += L'\n'; if (i + 1 < in.size() && in[i + 1] == L'\n') ++i; }
        else out += c;
    }
    return out;
}

static std::wstring FileNameOf(const std::wstring& p) {
    size_t s = p.find_last_of(L"\\/");
    return s == std::wstring::npos ? p : p.substr(s + 1);
}

// 파일을 읽어 와이드 문자열로 변환 (BOM 기반 인코딩 자동 감지)
static bool ReadFileToW(const std::wstring& path, std::wstring& out) {
    HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                           OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER sz;
    if (!GetFileSizeEx(h, &sz)) { CloseHandle(h); return false; }
    std::string bytes;
    bytes.resize((size_t)sz.QuadPart);
    DWORD rd = 0;
    if (sz.QuadPart > 0 && !ReadFile(h, &bytes[0], (DWORD)bytes.size(), &rd, nullptr)) {
        CloseHandle(h); return false;
    }
    CloseHandle(h);
    bytes.resize(rd);

    const unsigned char* b = (const unsigned char*)bytes.data();
    size_t nb = bytes.size();
    if (nb >= 3 && b[0] == 0xEF && b[1] == 0xBB && b[2] == 0xBF) {        // UTF-8 BOM
        out = Utf8ToW(std::string(bytes.begin() + 3, bytes.end()));
        return true;
    }
    if (nb >= 2 && b[0] == 0xFF && b[1] == 0xFE) {                        // UTF-16 LE
        out.assign((const wchar_t*)(b + 2), (nb - 2) / 2);
        return true;
    }
    if (nb >= 2 && b[0] == 0xFE && b[1] == 0xFF) {                        // UTF-16 BE
        size_t cnt = (nb - 2) / 2;
        out.resize(cnt);
        for (size_t i = 0; i < cnt; ++i) out[i] = (wchar_t)((b[2 + i * 2] << 8) | b[3 + i * 2]);
        return true;
    }
    if (nb == 0) { out.clear(); return true; }

    // BOM이 없으면 UTF-8 우선, 실패 시 시스템 ANSI(예: CP949)로 해석
    int wl = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, bytes.data(), (int)nb, nullptr, 0);
    if (wl > 0) {
        out.resize(wl);
        MultiByteToWideChar(CP_UTF8, 0, bytes.data(), (int)nb, &out[0], wl);
        return true;
    }
    int al = MultiByteToWideChar(CP_ACP, 0, bytes.data(), (int)nb, nullptr, 0);
    out.resize(al);
    if (al > 0) MultiByteToWideChar(CP_ACP, 0, bytes.data(), (int)nb, &out[0], al);
    return true;
}

// 문서를 UTF-8(개행 CRLF)로 저장
static bool WriteWToFile(const std::wstring& path, const std::wstring& md) {
    std::wstring norm; norm.reserve(md.size() + 16);
    for (wchar_t c : md) { if (c == L'\n') { norm += L'\r'; norm += L'\n'; } else norm += c; }
    std::string utf8 = WToUtf8(norm);
    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr,
                           CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    DWORD wr = 0; BOOL ok = TRUE;
    if (!utf8.empty()) ok = WriteFile(h, utf8.data(), (DWORD)utf8.size(), &wr, nullptr);
    CloseHandle(h);
    return ok != FALSE;
}

// 편집 컨트롤의 현재 텍스트를 \n 정규화하여 반환
static std::wstring GetEditText() {
    int len = GetWindowTextLengthW(g_hEdit);
    if (len <= 0) return L"";
    std::wstring w; w.resize(len);
    GetWindowTextW(g_hEdit, &w[0], len + 1);
    return NormalizeNewlines(w);
}

// RTF 스트림 입력 콜백
struct RtfBuf { const char* p; size_t len; size_t pos; };
static DWORD CALLBACK StreamInCB(DWORD_PTR ck, LPBYTE buf, LONG cb, LONG* pcb) {
    RtfBuf* s = (RtfBuf*)ck;
    LONG rem = (LONG)(s->len - s->pos);
    LONG c = cb < rem ? cb : rem;
    if (c > 0) { memcpy(buf, s->p + s->pos, (size_t)c); s->pos += c; }
    *pcb = c;
    return 0;
}

// ===================== UI 상태 =====================

static void UpdateTitle() {
    if (!g_hWndMain) return;
    std::wstring t;
    if (g_dirty) t += L"* ";
    t += g_filePath.empty() ? L"제목 없음" : FileNameOf(g_filePath);
    t += L" - MDRW [";
    t += (g_mode == Mode::Read ? L"읽기" : L"편집");
    t += L"]";
    SetWindowTextW(g_hWndMain, t.c_str());
}

static void UpdateMenuChecks() {
    HMENU m = GetMenu(g_hWndMain);
    if (!m) return;
    CheckMenuRadioItem(m, IDM_READMODE, IDM_EDITMODE,
                       g_mode == Mode::Read ? IDM_READMODE : IDM_EDITMODE, MF_BYCOMMAND);
}

// 현재 모드(g_mode)와 문서(g_markdown)를 컨트롤에 반영
static void ApplyMode() {
    g_suppress = true;
    SendMessageW(g_hEdit, EM_SETREADONLY, FALSE, 0);
    SendMessageW(g_hEdit, WM_SETTEXT, 0, (LPARAM)L"");   // EM_SETTEXTMODE 전 비우기

    if (g_mode == Mode::Read) {
        SendMessageW(g_hEdit, EM_SETTEXTMODE, TM_RICHTEXT, 0);
        std::string rtf = MarkdownToRtf(g_markdown);
        RtfBuf rb{ rtf.data(), rtf.size(), 0 };
        EDITSTREAM es{};
        es.dwCookie = (DWORD_PTR)&rb;
        es.pfnCallback = StreamInCB;
        SendMessageW(g_hEdit, EM_STREAMIN, SF_RTF, (LPARAM)&es);
        SendMessageW(g_hEdit, EM_SETSEL, 0, 0);
        SendMessageW(g_hEdit, EM_SETREADONLY, TRUE, 0);
    } else {
        SendMessageW(g_hEdit, EM_SETTEXTMODE, TM_PLAINTEXT, 0);
        CHARFORMAT2W cf{};
        cf.cbSize = sizeof(cf);
        cf.dwMask = CFM_FACE | CFM_SIZE | CFM_COLOR;
        lstrcpynW(cf.szFaceName, L"Consolas", LF_FACESIZE);
        cf.yHeight = 220;                       // 11pt (1/20 pt 단위)
        cf.crTextColor = RGB(30, 30, 30);
        SendMessageW(g_hEdit, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);

        std::wstring disp; disp.reserve(g_markdown.size() + 16);
        for (wchar_t c : g_markdown) { if (c == L'\n') disp += L"\r\n"; else disp += c; }
        SendMessageW(g_hEdit, WM_SETTEXT, 0, (LPARAM)disp.c_str());
        SendMessageW(g_hEdit, EM_SETSEL, 0, 0);
    }

    g_suppress = false;
    UpdateMenuChecks();
    UpdateTitle();
}

static void SyncFromEditor() {
    if (g_mode == Mode::Edit && g_hEdit) g_markdown = GetEditText();
}

static bool DoSave(bool saveAs);

// 변경 내용이 있으면 저장 여부를 묻는다. 취소 시 false.
static bool MaybeSave() {
    SyncFromEditor();
    if (!g_dirty) return true;
    int r = MessageBoxW(g_hWndMain, L"변경 내용을 저장하시겠습니까?", L"MDRW",
                        MB_YESNOCANCEL | MB_ICONEXCLAMATION);
    if (r == IDCANCEL) return false;
    if (r == IDYES) return DoSave(false);
    return true;   // 저장 안 함
}

static bool DoSave(bool saveAs) {
    SyncFromEditor();
    std::wstring path = g_filePath;
    if (saveAs || path.empty()) {
        wchar_t file[MAX_PATH] = L"";
        if (!path.empty()) lstrcpynW(file, FileNameOf(path).c_str(), MAX_PATH);
        OPENFILENAMEW ofn{};
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = g_hWndMain;
        ofn.lpstrFilter = L"마크다운 파일 (*.md)\0*.md;*.markdown\0텍스트 파일 (*.txt)\0*.txt\0모든 파일 (*.*)\0*.*\0";
        ofn.lpstrFile = file;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrDefExt = L"md";
        ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST | OFN_EXPLORER;
        if (!GetSaveFileNameW(&ofn)) return false;
        path = file;
    }
    if (!WriteWToFile(path, g_markdown)) {
        MessageBoxW(g_hWndMain, L"파일을 저장하지 못했습니다.", L"MDRW", MB_OK | MB_ICONERROR);
        return false;
    }
    g_filePath = path;
    g_dirty = false;
    UpdateTitle();
    return true;
}

static void DoOpen() {
    if (!MaybeSave()) return;
    wchar_t file[MAX_PATH] = L"";
    OPENFILENAMEW ofn{};
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = g_hWndMain;
    ofn.lpstrFilter = L"마크다운 파일 (*.md, *.markdown, *.txt)\0*.md;*.markdown;*.txt\0모든 파일 (*.*)\0*.*\0";
    ofn.lpstrFile = file;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_EXPLORER;
    if (!GetOpenFileNameW(&ofn)) return;

    std::wstring text;
    if (!ReadFileToW(file, text)) {
        MessageBoxW(g_hWndMain, L"파일을 열지 못했습니다.", L"MDRW", MB_OK | MB_ICONERROR);
        return;
    }
    g_markdown = NormalizeNewlines(text);
    g_filePath = file;
    g_dirty = false;
    g_mode = Mode::Read;     // 파일을 열면 읽기 모드로 보여 준다
    ApplyMode();
}

static void DoNew() {
    if (!MaybeSave()) return;
    g_markdown.clear();
    g_filePath.clear();
    g_dirty = false;
    g_mode = Mode::Edit;     // 새 문서는 편집 모드로 시작
    ApplyMode();
    SetFocus(g_hEdit);
}

static void SetMode(Mode m) {
    if (g_mode == m) return;
    if (g_mode == Mode::Edit) SyncFromEditor();
    g_mode = m;
    ApplyMode();
    if (m == Mode::Edit) SetFocus(g_hEdit);
}

// 메뉴를 런타임에 생성 (와이드 문자열이라 인코딩 문제 없음)
static HMENU BuildMenu() {
    HMENU bar = CreateMenu();

    HMENU file = CreatePopupMenu();
    AppendMenuW(file, MF_STRING, IDM_NEW,    L"새로 만들기(&N)\tCtrl+N");
    AppendMenuW(file, MF_STRING, IDM_OPEN,   L"열기(&O)...\tCtrl+O");
    AppendMenuW(file, MF_STRING, IDM_SAVE,   L"저장(&S)\tCtrl+S");
    AppendMenuW(file, MF_STRING, IDM_SAVEAS, L"다른 이름으로 저장(&A)...\tCtrl+Shift+S");
    AppendMenuW(file, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(file, MF_STRING, IDM_EXIT,   L"끝내기(&X)\tAlt+F4");
    AppendMenuW(bar, MF_POPUP, (UINT_PTR)file, L"파일(&F)");

    HMENU mode = CreatePopupMenu();
    AppendMenuW(mode, MF_STRING, IDM_READMODE, L"읽기 모드(&R)\tCtrl+R");
    AppendMenuW(mode, MF_STRING, IDM_EDITMODE, L"편집 모드(&E)\tCtrl+E");
    AppendMenuW(bar, MF_POPUP, (UINT_PTR)mode, L"모드(&M)");

    HMENU help = CreatePopupMenu();
    AppendMenuW(help, MF_STRING, IDM_ABOUT, L"정보(&A)...");
    AppendMenuW(bar, MF_POPUP, (UINT_PTR)help, L"도움말(&H)");

    return bar;
}

// 처음 보여 줄 환영 문서
static const wchar_t* kWelcome =
L"# MDRW 마크다운 리더 / 에디터\n"
L"\n"
L"**MDRW**에 오신 것을 환영합니다. 마크다운 파일을 *보기 좋게* 읽고, 간단히 편집할 수 있는 프로그램입니다.\n"
L"\n"
L"## 사용 방법\n"
L"\n"
L"- **읽기 모드** (`Ctrl+R`): 마크다운 문법에 맞춰 서식이 적용된 문서를 봅니다.\n"
L"- **편집 모드** (`Ctrl+E`): 메모장처럼 원본 텍스트를 직접 편집합니다.\n"
L"- `Ctrl+O` 파일 열기 · `Ctrl+S` 저장 · `Ctrl+N` 새 문서\n"
L"\n"
L"## 지원하는 문법\n"
L"\n"
L"1. 제목 (`#` ~ `######`)\n"
L"2. **굵게**, *기울임*, ***굵은 기울임***\n"
L"3. `인라인 코드` 와 아래의 코드 블록\n"
L"4. 목록 · 인용문 · 구분선 · [링크](https://www.google.com)\n"
L"\n"
L"> 인용문은 이렇게 표시됩니다.\n"
L">\n"
L"> 여러 줄도 가능합니다.\n"
L"\n"
L"```\n"
L"// 코드 블록 예시\n"
L"int main() {\n"
L"    printf(\"Hello, MDRW!\\n\");\n"
L"    return 0;\n"
L"}\n"
L"```\n"
L"\n"
L"## 표\n"
L"\n"
L"| 기능 | 단축키 | 설명 |\n"
L"|:-----|:------:|:-----|\n"
L"| 열기 | `Ctrl+O` | 파일 열기 |\n"
L"| 저장 | `Ctrl+S` | 현재 문서 저장 |\n"
L"| 모드 전환 | `Ctrl+R` / `Ctrl+E` | 읽기 / 편집 |\n"
L"\n"
L"---\n"
L"\n"
L"편집을 시작하려면 **편집 모드**(`Ctrl+E`)로 전환하세요. 즐거운 마크다운 작성 되세요!\n";

// ===================== 진입점 =====================

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MDRW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        return FALSE;
    }

    // 단축키 테이블을 런타임에 생성
    ACCEL acc[] = {
        { (BYTE)(FVIRTKEY | FCONTROL),          'N', IDM_NEW },
        { (BYTE)(FVIRTKEY | FCONTROL),          'O', IDM_OPEN },
        { (BYTE)(FVIRTKEY | FCONTROL),          'S', IDM_SAVE },
        { (BYTE)(FVIRTKEY | FCONTROL | FSHIFT), 'S', IDM_SAVEAS },
        { (BYTE)(FVIRTKEY | FCONTROL),          'R', IDM_READMODE },
        { (BYTE)(FVIRTKEY | FCONTROL),          'E', IDM_EDITMODE },
    };
    g_hAccel = CreateAcceleratorTableW(acc, (int)(sizeof(acc) / sizeof(acc[0])));

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        if (!TranslateAccelerator(g_hWndMain, g_hAccel, &msg)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (g_hAccel) DestroyAcceleratorTable(g_hAccel);
    return (int)msg.wParam;
}

//  창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MDRW));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = nullptr;   // 메뉴는 런타임에 직접 설정
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}

//  인스턴스 핸들을 저장하고 주 창을 만듭니다.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1000, 720, nullptr, nullptr, hInstance, nullptr);
    if (!hWnd) return FALSE;

    g_hWndMain = hWnd;
    SetMenu(hWnd, BuildMenu());
    UpdateMenuChecks();

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    return TRUE;
}

//  주 창의 메시지를 처리합니다.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        g_hWndMain = hWnd;
        g_richLib = LoadLibraryW(L"Msftedit.dll");   // RICHEDIT50W 등록
        g_hEdit = CreateWindowExW(0, MSFTEDIT_CLASS, L"",
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_NOHIDESEL,
            0, 0, 0, 0, hWnd, (HMENU)IDC_EDIT, hInst, nullptr);

        SendMessageW(g_hEdit, EM_EXLIMITTEXT, 0, (LPARAM)0x7FFFFFFE);
        SendMessageW(g_hEdit, EM_SETEVENTMASK, 0, ENM_CHANGE | ENM_LINK);
        SendMessageW(g_hEdit, EM_AUTOURLDETECT, TRUE, 0);   // 본문 속 URL 자동 인식
        SendMessageW(g_hEdit, EM_SETBKGNDCOLOR, 0, (LPARAM)RGB(255, 255, 255));
        SendMessageW(g_hEdit, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELPARAM(28, 28));

        g_markdown = kWelcome;
        g_filePath.clear();
        g_dirty = false;
        g_mode = Mode::Read;
        ApplyMode();
        return 0;
    }
    case WM_SIZE:
        if (g_hEdit) MoveWindow(g_hEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
        return 0;
    case WM_SETFOCUS:
        if (g_hEdit) SetFocus(g_hEdit);
        return 0;
    case WM_COMMAND:
    {
        // 편집 컨트롤 변경 알림
        if (HIWORD(wParam) == EN_CHANGE && (HWND)lParam == g_hEdit) {
            if (!g_suppress && g_mode == Mode::Edit && !g_dirty) { g_dirty = true; UpdateTitle(); }
            return 0;
        }
        switch (LOWORD(wParam))
        {
        case IDM_NEW:      DoNew(); break;
        case IDM_OPEN:     DoOpen(); break;
        case IDM_SAVE:     DoSave(false); break;
        case IDM_SAVEAS:   DoSave(true); break;
        case IDM_READMODE: SetMode(Mode::Read); break;
        case IDM_EDITMODE: SetMode(Mode::Edit); break;
        case IDM_ABOUT:    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About); break;
        case IDM_EXIT:     SendMessageW(hWnd, WM_CLOSE, 0, 0); break;
        default:           return DefWindowProc(hWnd, message, wParam, lParam);
        }
        return 0;
    }
    case WM_NOTIFY:
    {
        NMHDR* nh = (NMHDR*)lParam;
        if (nh->code == EN_LINK) {
            ENLINK* el = (ENLINK*)lParam;
            if (el->msg == WM_LBUTTONUP) {
                LONG cnt = el->chrg.cpMax - el->chrg.cpMin;
                if (cnt > 0 && cnt < 2048) {
                    struct { CHARRANGE chrg; LPWSTR lpstrText; } tr;
                    std::wstring url; url.resize((size_t)cnt + 1);
                    tr.chrg = el->chrg;
                    tr.lpstrText = &url[0];
                    SendMessageW(g_hEdit, EM_GETTEXTRANGE, 0, (LPARAM)&tr);
                    url.resize((size_t)cnt);
                    ShellExecuteW(hWnd, L"open", url.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
                }
            }
            return 0;
        }
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    case WM_CLOSE:
        if (MaybeSave()) DestroyWindow(hWnd);
        return 0;
    case WM_DESTROY:
        if (g_richLib) { FreeLibrary(g_richLib); g_richLib = nullptr; }
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
