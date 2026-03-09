// AlgoStudy.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "Picnic.h"
#include "BoardCover.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

int node[101][101] = { 0, };
int linked[101] = { 0, };	//	n에 연결된 노드의 수
int desc[101] = { 0, };	//	나를 기준으로 전체 하위 노드의 수

int CalcLinked(int n, int parent)
{
	int ret = 1;
	for (int i = 0; i < linked[n]; i++)
	{
		if (node[n][i] == parent)
		{	//	부모 = 이미 방문한 노드
			continue;
		}

		ret += (CalcLinked(node[n][i], n));
	}
	
	desc[n] = ret;

	return ret;
}

// wires_rows는 2차원 배열 wires의 행 길이, wires_cols는 2차원 배열 wires의 열 길이입니다.
int solution(int n, int** wires, size_t wires_rows, size_t wires_cols) {
	int answer = -1;
	
	for (int i = 0; i < wires_rows; i++)
	{
		int a = wires[i][0];
		int b = wires[i][1];
		node[a][linked[a]] = b;	linked[a]++;	//	a노드에 연결된 노드의 수를 증가 & 해당 노드의 번호
		node[b][linked[b]] = a;	linked[b]++;
	}

	CalcLinked(1, 0);
	int min = 9999999;
	for (int i = 0; i < 101; i++)
	{
		int sub = abs(n - (2 * desc[i]));
		if (sub < min)
		{
			min = sub;
		}
	}
	answer = min;
	return answer;
}


int main(void)
{
	
	return 0;
}

/*
int main()
{
	std::cout << "Hello World!\n";


	int numOfStudent = 6;

	int friendsList[10][2] = { {0,1},{0,2},{1,2},{1,3},{1,4},{2,3},{2,4},{3,4},{3,5},{4,5} };

	int out = picnic(numOfStudent, friendsList);
	std::cout<< out;
	std::cout<<std::endl;

  
	//  보드커버 테스트용 입력 만들기
	std::vector<std::vector<int>> board;

	for (int i = 0; i < 10; i++)
	{
		std::vector<int> line;
		for (int j = 0; j < 8; j++)
		{
			if (j == 0 || j == 7 || i == 0 || i == 9)
			{
				line.push_back(1);
			}
			else
			{
				line.push_back(0);
			}
		}
		board.push_back(line);
	}

	int bcOut = 0;
	bcOut = BoardCover(board);

	std::cout << bcOut;
	std::cout << std::endl;


}*/

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
