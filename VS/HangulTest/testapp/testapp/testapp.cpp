// testapp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>

#include <deque>

using namespace std;

class CGraphic
{
private:
	CGraphic();
	~CGraphic();

	struct point
	{
		int X;
		int Y;
	};

public:

	typedef enum
	{
		blank = 0,
		square,
		triangle,
		circle,
		horizontalLine,
		verticalLine,
		cross,


		PixelMax,
	}Pixel;		//	미리 정의해야하는 픽셀 모양들입니다.

	typedef enum
	{
		TEXT_FOREGROUND_BLUE = FOREGROUND_BLUE,
		TEXT_FOREGROUND_GREEN = FOREGROUND_GREEN,
		TEXT_FOREGROUND_RED = FOREGROUND_RED,
		TEXT_FOREGROUND_YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		TEXT_FOREGROUND_MAGENTA = FOREGROUND_BLUE | FOREGROUND_RED,
		TEXT_FOREGROUND_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
		TEXT_FOREGROUND_GRAY = TEXT_FOREGROUND_RED | TEXT_FOREGROUND_BLUE | TEXT_FOREGROUND_GREEN,
		TEXT_FOREGROUND_WHITE = TEXT_FOREGROUND_GRAY | FOREGROUND_INTENSITY,
		TEXT_FOREGROUND_BLACK = 0,

		TEXT_BACKGROUND_BLUE = BACKGROUND_BLUE,
		TEXT_BACKGROUND_GREEN = BACKGROUND_GREEN,
		TEXT_BACKGROUND_RED = BACKGROUND_RED,
		TEXT_BACKGROUND_YELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		TEXT_BACKGROUND_MAGENTA = BACKGROUND_BLUE | BACKGROUND_RED,
		TEXT_BACKGROUND_CYAN = BACKGROUND_BLUE | BACKGROUND_GREEN,
		TEXT_BACKGROUND_GRAY = TEXT_BACKGROUND_RED | TEXT_BACKGROUND_BLUE | TEXT_BACKGROUND_GREEN,
		TEXT_BACKGROUND_WHITE = TEXT_BACKGROUND_GRAY | BACKGROUND_INTENSITY,
		TEXT_BACKGROUND_BLACK = 0,

	}TextColor;	//	텍스트 컬러입니다. 글자색|배경색 -> 비트연산자로 합성하세요

	static CGraphic* GetInstance();		//	싱글톤 인스턴스 가져오기
	static void Release();				//	사용이 끝나면 정리


	//	버퍼에 픽셀 하나를 그립니다.
	void RenderToBuffer(int x, int y, Pixel type, TextColor color);

	//	버퍼를 화면에 출력합니다
	//	각 프레임의 시작에 StartDraw()를 호출합니다.
	//	각 프레임의 끝에 EndDraw()를 호출합니다.
	void StartDraw();
	void EndDraw();

	//	로그를 추가합니다
	void AddLog(string str);


private:

	struct Shader
	{
		Pixel vertex = blank;
		TextColor color = TEXT_BACKGROUND_BLACK;
	};

	//	초기화를 위한 함수들입니다.
	void SetPixelText();

	//	커서를 화면에 맞게 리사이징한 위치를 설정합니다.
	void SetCursorPos(int x, int y);

	//	버퍼에 배경색을 채웁니다
	void DrawBackground(TextColor color);

	//	각 화면 영역의 테두리를 그립니다
	void DrawShape();

	//	로그 영역을 지웁니다
	void ClearLog();

protected:

	static CGraphic* m_pInstance;		//	싱글톤 인스턴스

	HANDLE m_hOP;						//	콘솔 아웃풋 핸들
	CONSOLE_CURSOR_INFO	m_CurInfo;		//	커서 정보

	string m_sPixels[Pixel::PixelMax];	//	픽셀 출력용 스트링

	vector<vector<Shader>> m_aPrevBuffer;	//	더블 버퍼링을 위한 이전버퍼
	vector<vector<Shader>> m_aBuffer;		//	메인 버퍼
	int m_iScreenSize;						//	메인 화면의 크기(정사각형)
	int m_iEndOfScreenX;					//	게임창의 끝 위치
	int m_iEndOfScreenY;					//	게임창의 끝 위치

	deque<string> m_aLog;			//	로그 큐
	int m_iMaxLog;					//	출력할 수 있는 최대 로그 메세지 수 입니다.

	TextColor m_DefaultBackgroundColor;	//	기본 배경 색입니다.

	bool m_bOnDraw;				//	그리기 중에만 작동해야 하는 함수들용
};

CGraphic* CGraphic::m_pInstance = nullptr;

CGraphic::CGraphic()
{
	//	콘솔 출력에 대한 기본 핸들을 가져옵니다
	m_hOP = GetStdHandle(STD_OUTPUT_HANDLE);
	SetPixelText();
	m_iScreenSize = 30;
	m_iEndOfScreenX = 43;
	m_iEndOfScreenY = 40;

	//	커서 투명화
	m_CurInfo.bVisible = 0;
	m_CurInfo.dwSize = 1;
	SetConsoleCursorInfo(m_hOP, &m_CurInfo);

	//	버퍼를 준비합니다
	m_aPrevBuffer.resize(30);
	m_aBuffer.resize(30);
	for (int i = 0; i < 30; i++)
	{
		m_aPrevBuffer[i].resize(30);
		m_aBuffer[i].resize(30);
	}

	//	멤버 변수들을 초기화합니다
	m_iMaxLog = 7;
	m_DefaultBackgroundColor = TextColor::TEXT_BACKGROUND_BLUE;
	m_bOnDraw = false;

	//	게임 레이아웃을 그려둡니다
	DrawShape();
}

CGraphic::~CGraphic()
{

}

void CGraphic::SetPixelText()
{//	여기서 픽셀의 형태를 정의하세요
	m_sPixels[blank] = "  ";
	m_sPixels[square] = "HH";
	m_sPixels[triangle] = "<>";
	m_sPixels[circle] = "()";
	m_sPixels[horizontalLine] = "--";
	m_sPixels[verticalLine] = "||";
	m_sPixels[cross] = "++";
}

CGraphic* CGraphic::GetInstance()
{//	싱글톤 구조입니다
	if (m_pInstance == nullptr)
	{
		m_pInstance = new CGraphic();
	}

	return m_pInstance;
}

void CGraphic::Release()
{//	사용이 종료되면 삭제해주세요
	if (m_pInstance == nullptr)
	{
		return;
	}

	delete m_pInstance;
	m_pInstance = nullptr;
}

//	커서의 위치를 변경합니다
void CGraphic::SetCursorPos(int x, int y)
{
	COORD cdPos;
	cdPos.X = x * 2;
	cdPos.Y = y;
	SetConsoleCursorPosition(m_hOP, cdPos);
}

void CGraphic::RenderToBuffer(int x, int y, CGraphic::Pixel type, CGraphic::TextColor color)
{
	if (!m_bOnDraw)	return;
	m_aBuffer[y][x].color = color;
	m_aBuffer[y][x].vertex = type;
}

//	배경을 그립니다.
void CGraphic::DrawBackground(CGraphic::TextColor color)
{
	if (!m_bOnDraw)	return;
	Shader s;
	s.color = color;
	for (auto& i : m_aBuffer)
	{
		fill(i.begin(), i.end(), s);
	}
}

void CGraphic::StartDraw()
{
	if (m_bOnDraw)	return;	//	StartDraw를 연속해서 두번 호출하지 마시오
	m_bOnDraw = true;
	DrawBackground(m_DefaultBackgroundColor);
}

//	버퍼를 화면에 그립니다.
void CGraphic::EndDraw()
{
	if (!m_bOnDraw)	return;	//	그리기중이 아닙니다.

	for (int y = 0; y < 30; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			//	이전 화면과 같은 내용이면 넘어갑니다
			if (m_aPrevBuffer[y][x].vertex == m_aBuffer[y][x].vertex &&
				m_aPrevBuffer[y][x].color == m_aBuffer[y][x].color)	continue;

			//	픽셀을 그립니다
			SetCursorPos(x + 1, y + 1);
			SetConsoleTextAttribute(m_hOP, m_aBuffer[y][x].color);
			cout << m_sPixels[m_aBuffer[y][x].vertex];
		}
	}

	//	그리기가 끝나면 색상을 초기화 합니다
	SetConsoleTextAttribute(m_hOP, TEXT_FOREGROUND_WHITE | TEXT_BACKGROUND_BLACK);
	//	더블버퍼링
	swap(m_aPrevBuffer, m_aBuffer);

	m_bOnDraw = false;	//	그리기가 끝났습니다.
}

//	로그를 출력합니다
void CGraphic::AddLog(string str)
{
	//	로그창을 지웁니다.
	ClearLog();

	//	새 로그를 큐에 넣습니다
	m_aLog.push_back(str);
	while (m_aLog.size() > m_iMaxLog)
	{	//	큐가 넘치면 오래된 로그를 제거합니다.
		m_aLog.pop_front();
	}

	//	로그를 다시 출력합니다.
	int logSize = (int)m_aLog.size();
	for (int i = 0; i < logSize; i++)
	{
		SetCursorPos(1, m_iScreenSize + 2 + i);
		cout << m_aLog[i];
	}
}

//	게임 틀을 그립니다.
void CGraphic::DrawShape()
{
	string line;
	line.resize(m_iEndOfScreenX * 2 + 2, ' ');
	SetConsoleTextAttribute(m_hOP, TextColor::TEXT_BACKGROUND_WHITE);
	SetCursorPos(0, 0);
	cout << line;
	SetCursorPos(0, m_iScreenSize + 1);
	cout << line;
	SetCursorPos(0, m_iEndOfScreenY);
	cout << line;

	for (int i = 1; i < m_iEndOfScreenY; i++)
	{
		SetCursorPos(0, i);
		cout << m_sPixels[Pixel::blank];
		SetCursorPos(m_iEndOfScreenX, i);
		cout << m_sPixels[Pixel::blank];

		if (i > m_iScreenSize + 1)	continue;
		SetCursorPos(m_iScreenSize + 1, i);
		cout << m_sPixels[Pixel::blank];
	}
}

//	로그 영역을 지웁니다(테두리 제외)
void CGraphic::ClearLog()
{
	string str;
	str.resize((m_iEndOfScreenX - 1) * 2, ' ');

	SetConsoleTextAttribute(m_hOP, TextColor::TEXT_BACKGROUND_BLACK);
	for (int i = m_iScreenSize + 3; i <= m_iScreenSize + m_iMaxLog + 2; i++)
	{
		SetCursorPos(1, i);
		cout << str;
	}
	SetConsoleTextAttribute(m_hOP, TextColor::TEXT_BACKGROUND_BLACK | TextColor::TEXT_FOREGROUND_WHITE);
}


int main()
{
	std::cout << "윈도우 10 이상의 콘솔창은 코드에서의 콘솔 창 크기 강제 조절이 동작하지 않을 수 있습니다.\n";
	std::cout << "게임을 시작하기 전에 콘솔 창 크기를 적절하게 조절 한 후 진행하시기 바랍니다.\n";
	std::cout << "아무 키를 눌러 계속합니다.\n";

	char in = _getch();

	///////////////////////////////////////////////
	//	여기서부터 게임 로직을 작성합니다
	///////////////////////////////////////////////

	///	게임에 필요한 객체들 준비 구간
	CGraphic* pGraphic = CGraphic::GetInstance();

	if (pGraphic == nullptr)
	{	//	엔진이 없습니다
		return 0;
	}

	//	그리기 테스트용
	CGraphic::Pixel pix = CGraphic::Pixel::circle;
	CGraphic::TextColor tex = static_cast<CGraphic::TextColor>(CGraphic::TextColor::TEXT_BACKGROUND_MAGENTA | CGraphic::TextColor::TEXT_FOREGROUND_CYAN);
	int x = 15;
	int y = 15;

	///	게임 루프
	while (1)
	{
		//	테스트 로직
		if (_kbhit())	//	이번 프레임에 입력이 있었는지 감지합니다.
		{	//	입력이 있었다면
			char input = _getch();	//	입력을 가져옵니다.

			switch (input)
			{	//	입력 내용을 확인하고 처리합니다.
			case 'w':
				y--;	//	*** 콘솔 그래픽은 4사분면((0, 0)의 위치가 좌상단)이므로 y축이 반대로 동작해야합니다. ***
				break;
			case 'a':
				x--;
				break;
			case 's':
				y++;
				break;
			case 'd':
				x++;
				break;
			}

			//	참고
			//← 좌측 방향키 : 75
			//
			//→ 우측 방향키 : 77
			//
			//↑ 위 방향키 : 72
			//
			//↓ 아래 방향키 : 80
			//
			//Enter키 : 13
		}

		pGraphic->StartDraw();


		//	테스트 그리기
		pGraphic->RenderToBuffer(x, y, pix, tex);


		pGraphic->EndDraw();
	}


	///////////////////////////////////////////////
	//	게임이 종료되었습니다. 종료처리를 작성해주세요
	///////////////////////////////////////////////

	CGraphic::Release();

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
