// MidiPrac.cpp : 콘솔 진입점.
// MIDI 파일을 파싱(CMidi)한 뒤 FluidSynth(사운드폰트) 또는 winmm으로 재생한다.

#include "MidiPlayer.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

static void PrintUsage()
{
	printf(
		"사용법: MidiPrac.exe [미디파일] [옵션]\n"
		"  -sf <파일>   사운드폰트(.sf2 등) 지정 (FluidSynth 백엔드)\n"
		"  -winmm       FluidSynth를 쓰지 않고 winmm(기본 GS 신스)으로 재생\n"
		"  -d <번호>    winmm 출력 장치 번호 지정 (-list 로 확인, -winmm 포함)\n"
		"  -list        winmm 출력 장치 목록 출력 후 종료\n"
		"  -auto        선택 메뉴 없이 자동 탐색으로 바로 재생\n"
		"인수가 없으면 ./goit.mid 를 재생한다. 백엔드 옵션(-sf/-winmm/-d/-auto)을\n"
		"주지 않으면 시작 시 출력(음원) 선택 메뉴가 표시된다.\n");
}

// ──────────────────────────────────────────────
// 출력(음원) 선택 메뉴.
// winmm 장치(Microsoft GS Wavetable Synth 포함)와 발견된 사운드폰트(.sf2)를
// 하나의 번호 목록으로 보여주고, 고른 항목을 opt에 반영한다.
// 그냥 Enter를 누르면 추천 기본값(사운드폰트가 있으면 첫 번째, 없으면 시스템 기본 winmm)을 쓴다.
// ──────────────────────────────────────────────
static void SelectOutputInteractive(PlayerOptions& opt)
{
	std::vector<std::string> devices = WinmmOut::DeviceNames();
	std::vector<std::string> fonts   = ScanSoundFonts();

	// 번호: [0 .. devices.size()-1] = winmm 장치, 그 다음 = 사운드폰트
	const size_t fontBase = devices.size();

	printf("\n출력(음원)을 선택하세요:\n");
	printf("  ── winmm 장치 (Windows 기본 신스) ──\n");
	for (size_t i = 0; i < devices.size(); i++)
		printf("  [%zu] %s\n", i, devices[i].c_str());

	if (!fonts.empty())
	{
		printf("  ── 사운드폰트 (FluidSynth) ──\n");
		for (size_t i = 0; i < fonts.size(); i++)
		{
			const std::string& p = fonts[i];
			size_t slash = p.find_last_of("\\/");
			std::string name = (slash == std::string::npos) ? p : p.substr(slash + 1);
			printf("  [%zu] %s\n", fontBase + i, name.c_str());
		}
	}

	// 추천 기본값: 사운드폰트가 있으면 첫 폰트, 없으면 첫 winmm 장치
	size_t def = fonts.empty() ? 0 : fontBase;
	printf("선택 번호 [기본 %zu]: ", def);
	fflush(stdout);

	// 한 줄 입력 → 숫자가 없으면(빈 줄 등) 기본값 사용
	size_t choice = def;
	char line[64] = {};
	if (fgets(line, sizeof(line), stdin))
	{
		const char* p = line;
		while (*p == ' ' || *p == '\t') p++;
		if (*p >= '0' && *p <= '9')
			choice = (size_t)strtoul(p, nullptr, 10);
	}

	if (choice < devices.size())                         // winmm 장치 선택
	{
		opt.winmmDevice = (int)choice;
		opt.forceWinmm  = true;
		opt.soundfont.clear();
	}
	else if (choice < fontBase + fonts.size())           // 사운드폰트 선택
	{
		opt.soundfont  = fonts[choice - fontBase];
		opt.forceWinmm = false;
	}
	// 범위 밖이면 opt를 그대로 둬서 기존 자동 탐색 로직이 처리하게 한다
}

int main(int argc, char* argv[])
{
	PlayerOptions opt;
	//opt.midiPath = "./goit.mid";   // 기본 파일 (작업 디렉터리 기준)
	opt.midiPath = "./take5.mid";   // 기본 파일 (작업 디렉터리 기준)

	// 백엔드를 CLI에서 직접 정했는지(-sf/-winmm/-d) 또는 -auto로 메뉴를 끄는지 추적.
	// 어느 쪽도 아니면 시작 시 출력 선택 메뉴를 띄운다.
	bool backendChosen = false;

	for (int i = 1; i < argc; i++)
	{
		std::string a = argv[i];
		if (a == "-sf" && i + 1 < argc)     { opt.soundfont = argv[++i]; backendChosen = true; }
		else if (a == "-d" && i + 1 < argc) { opt.winmmDevice = atoi(argv[++i]); opt.forceWinmm = true; backendChosen = true; }
		else if (a == "-winmm")             { opt.forceWinmm = true; backendChosen = true; }
		else if (a == "-auto")                backendChosen = true;   // 메뉴 없이 자동 탐색
		else if (a == "-list")              { WinmmOut::ListDevices(); return 0; }
		else if (a == "-h" || a == "--help" || a == "/?") { PrintUsage(); return 0; }
		else                                  opt.midiPath = a;   // 옵션이 아니면 파일 경로
	}

	if (!backendChosen)
		SelectOutputInteractive(opt);   // 출력(음원) 선택 메뉴

	MidiPlayer player(opt);   // 생성자에서 파일 헤더·트랙·이벤트를 모두 파싱한다
	player.Play();            // 시간순 송출 + 키 조작 (키 목록은 재생 화면에 표시)
	return 0;
}
