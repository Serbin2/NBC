//	완전 탐색 예제
//	155p 소풍 문제
//	친구끼리 짝을 지어주는 방법의 수를 계산하기

//	입력 : 첫줄에 테스트 케이스 수 C ( C <= 50 )
//	각 테스트 케이스의 첫줄에는 학생의 수 n ( 2 <= n <= 10 )와 친구 쌍의 수 m ( 0 <= m <= n( n - 1 ) / 2 )
//	그 다음줄에 m개의 정수쌍으로 친구인 두 학생의 번호가 주어집니다.
//	학생의 수는 짝수입니다.

//	친구가 없는 학생은 없는가보다


//	첫번째 학생을 기준으로 탐색을 시작한다.
//	첫번째 학생의 친구를 찾아 짝을 짓는다.
//	짝이 지어진 학생들은 배열에서 제외한다.
//	남은 학생중 앞의 학생부터 다시 탐색을 시작한다.
//	배열에 학생이 남지 않으면 짝이 완성되었다.
//	마지막으로 지어진 짝부터 해산하며 그 다음 짝을 짓는 경우의 수가 있는지 확인한다.

#include	"Picnic.h"

int MakeGroup(bool students[10], bool list[10][10]);


//	경우의 수를 찾기위한 함수
int picnic( int numOfStudents, int friendsList[10][2])
{	//	친구의 수와 친구쌍의 목록을 입력으로 받습니다
	
	//	학생 목록을 만듧니다
	bool students[10] = { 0 };
	for (int i = 0; i < 10; i++)
	{
		if (i >= numOfStudents)
		{
			students[i] = true;
		}
	}

	bool friends[10][10] = { 0 };

	for (int i = 0; i < 10; i++)
	{
		friends[friendsList[i][0]][friendsList[i][1]] = true;
		//friends[friendsList[i][1]][friendsList[i][0]] = true;
	}


	return MakeGroup(students, friends);
}

//	학생수가 최대 10명이므로 10크기의 배열을 사용
//	bool값이 true이면 짝이 지어진 것
//	list[x][y] 의 값이 true이면 x와 y는 친구
int MakeGroup(bool students[10], bool list[10][10])
{	//	아직 짝이 아닌 학생 목록을 받아 짝을 찾아주도록 한다
	
	int first = -1;
	int ret = 0;

	for (int i = 0; i < 10; i++)
	{
		if (!students[i])
		{
			//	아직 짝이 지어지지 않은 학생이 있습니다.
			first = i;
			break;
		}
	}
	
	if (first == -1)
	{	//	짝이 모두 지어졌습니다.
		return 1;
	}

	for (int n = first + 1; n < 10; n++)
	{
		if (students[n])
		{	//	나도 이미 짝이 있어요
			continue;
		}

		if (list[first][n])
		{	//	우린 친구에요
			students[first] = students[n] = true;	//	짝이 지어졌습니다.
			ret += MakeGroup(students, list);	//	남는 학생들로 다시 짝을 지을 수 있는 경우의 수를 찾습니다.
			students[first] = students[n] = false;	//	짝을 해산하고 다음 경우의 수를 찾습니다.
		}
	}

	return ret;
}
