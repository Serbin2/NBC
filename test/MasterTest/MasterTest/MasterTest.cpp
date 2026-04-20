// MasterTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

//#define Q01
#ifdef Q01
#include <iostream>
#include <string>
using namespace std;

// s가 팰린드롬이면 1, 아니면 0 반환
int solution(const string& s) {
	// TODO 여기에 코드를 작성하세요
	int size = s.size();
	//	size 기준으로 앞뒤에서 읽기
	if (size == 0)	return 0;	//	빈문자열
	
	int half = size / 2;
	while (half != 0)
	{	//	다 읽으면 팰린드롬이 맞음

		if (s[0 + half] != s[size - 1 - half])
		{
			return 0;
		}
		half--;
	}


	return 1;
}

int main() {
	cout << solution("racecar") << endl;  // 1
	cout << solution("hello") << endl;  // 0
	cout << solution("abcba") << endl;  // 1
	cout << solution("") << endl;  // 0
	cout << solution("a") << endl;  // 1
	return 0;
}
#endif

//#define Q02
#ifdef Q02
#include <iostream>
#include <vector>
using namespace std;

int viewed[1000][1000];

int checkIsle(vector<vector<int>>& grid, int x, int y)
{	//	x, y 좌표와 연결된 섬 찾기
	//	상하좌우 순회하며 연결되어있으면 본것으로 체크
	
	//범위 밖
	if (x < 0)	return 0;
	if (y < 0)	return 0;
	if (x >= grid.size())	return 0;
	if (y >= grid.size())	return 0;

	//	섬 아님
	if (grid[x][y] == 0)	return 0;
	if (viewed[x][y] == 1)	return 0;	//	이미 봄

	viewed[x][y] = 1;	//나는 섬이다

	//	주변 확인
	checkIsle(grid, x, y - 1);
	checkIsle(grid, x, y + 1);
	checkIsle(grid, x + 1, y);
	checkIsle(grid, x - 1, y);

	return 1;
}

int solution(vector<vector<int>>& grid) {
	// TODO 여기에 코드를 작성하세요
	int ret = 0;

	for (int x = 0; x < grid.size(); x++)
	{
		for (int y = 0; y < grid[x].size(); y++)
		{//	2차원 배열 순회하며 섬 찾기
			ret += checkIsle(grid, x, y);
		}
	}


	return ret;
}

int main() {
	vector<vector<int>> g1 = {
		{1, 1, 0, 0},
		{1, 0, 0, 1},
		{0, 0, 1, 1}
	};
	cout << solution(g1) << endl; // 2

	vector<vector<int>> g2 = {
		{1, 1, 1},
		{1, 1, 1}
	};
	cout << solution(g2) << endl; // 1

	vector<vector<int>> g3 = {
		{0, 0},
		{0, 0}
	};
	cout << solution(g3) << endl; // 0
	return 0;
}


#endif


//	Q03 반사 벡터 계산

/*
당신은 **1인칭 슈팅 게임의 총알 반사 시스템**을 구현하는 개발자입니다.

총알이 벽면에 충돌했을 때, 물리적으로 올바른 방향으로 튕겨나가야 합니다.

**"입사 벡터(총알 진행 방향)와 벽의 법선 벡터(normal)가 주어질 때, 반사 벡터를 어떻게 수학적으로 구할 수 있는가?"**

- 수학적 공식을 유도하고, 게임 코드에 적용 가능한 형태로 설명할 것.
- 내적(dot product)을 반드시 활용할 것.

두 벡터의 내적은 두 벡터 사이의 각도를 구하는 연산이다.
벽의 노말을 기준으로 입사 벡터 사이의 각과 반사 벡터 사이의 각은 동일해야 한다
구한 각을 기준으로 벡터를 회전시킨다면..

*/


//	Q04 virtual 
//	2

//	Q05	volatile


//	Q06
//	1

//	Q07
//	4

//	Q08
/*
	스마트 포인터 안써봐서 잘은 모르겠지만 두 객체가 서로 참조를 하는 상황이 되면서 주종 관계가 모호해지므로 참조 카운트가 무한이 참조되거나 삭제시 무한히 삭제되려 하는 문제가 발생할 것으로 예상됩니다.
	shared_ptr 대신 Weak_ptr를 활용해 참조는 하되 참조 카운트는 증감시키지 않도록 하여 순환 참조로 인한 참조 카운트 문제를 예방할 수 있을 것 같습니다.
	다만 이 경우엔 weak_ptr가 유효한지 확인해야 하는 작업이 추가로 발생할 수 있을 것으로 보입니다.
*/

//	Q09
/*
	설계 B가 유리합니다.
	Enemy 데이터의 크기가 커진다면 Array가 차지하는 그 용량 또한 엄청나게 비대해질 것입니다.
	그러나 B 방식의 경우 위치 등 변경되는 데이터 외에 나머지 데이터들(모델링이나 애니메이션 등)이 동일하다는 기준으로 기준이 되는 데이터 하나만 메모리에 올려놓고 화면에 그리는 등의 작업이 필요할 때에는 기준 데이터를 참조하고 위치같은 개별 데이터만 해당하는 개별 배열에서 참조하게 할 수 있습니다.
	이 경우, 중복되는 데이터를 메모리에 올리지 않아도 되므로 메모리 절약 차원에서 이득을 볼 수도 있으며 위치 정보 등 변경되는 데이터 사이에 다른 정보가 없는 연속된 배열의 형태가 되어 캐시를 이용한 접근속도에서도 이득을 챙길 수 있습니다.

*/