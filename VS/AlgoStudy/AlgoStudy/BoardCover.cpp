#include "BoardCover.h"

//	H * W 크기의 게임판을 덮기
//	L모양의 3칸짜리 블록으로 덮는다
//	중복으로 덮거나 게임판 밖으로 나가면 안된다.
//	주어진 게임판을 완전히 덮는 경우의 수를 출력

//	1 <= H, w <= 20
//	게임판의 빈칸의 수는 50을 넘지 않는다.


//	중복을 제거하기 위해,
//	게임판의 위쪽, 왼쪽부터 블록을 채워나갑니다.
//	검사하는 칸 기준으로 위쪽칸들과 같은 줄의 왼쪽칸들은 이미 채워져있다고 가정합니다.

//	방향에 따른 블록 종류
//	기준 칸에 대한 상대 좌표입니다.
const int BlockType[4][3][2] = {
	{ { 0, 0 }, { 1, 0 }, { 0, 1 } },	//	r
	{ { 0, 0 }, { 0, 1 }, { 1, 1 } },	//	ㄱ
	{ { 0, 0 }, { 1, 0 }, { 1, 1 } },	//	ㄴ
	{ { 0, 0 }, { 0, 1 }, { -1, 1 } }	//	j
};

int SetBlock(std::vector<std::vector<int>>& board);

int BoardCover(std::vector<std::vector<int>> board)
{
	//	보드의 빈칸 수를 먼저 계산합니다
	int height = (int)board.size();
	int width = (int)board[0].size();

	int white = 0;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (board[y][x] == 0)
			{	//	0은 빈칸으로 간주합니다
				//	0이 아니면 채워진 칸입니다.
				white++;
			}
		}
	}

	//	빈칸의 수가 3의 배수가 아니라면 불가능한 문제입니다.
	if (white % 3 != 0)
	{
		return 0;
	}

	int ret = 0;

	ret = SetBlock(board);

	return ret;
}


int SetBlock(std::vector<std::vector<int>>& board)
{	//	왼쪽 위의 첫번째 빈칸을 찾습니다.
	//	빈칸을 기준으로 네가지 방향대로 블록을 놓습니다.
	//	블록을 놓은 위치가 유효한지 확인합니다.
	//	유효하다면 다음 블록을 놓도록 합니다.(재귀)
	//	유효하지 않다면 다음 방향으로 블록을 놓습니다.
	//	네가지 방향을 모두 검사한 후 종료합니다.
	int retVal = 0;

	int height = (int)board.size();
	int width = (int)board[0].size();

	//	상단 왼쪽 첫번째 흰색 칸을 찾습니다.
	int x = -1;
	int y = -1;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (board[j][i] == 0)
			{	
				x = i;
				y = j;
				break;
			}
		}
		if (y != -1)	break;
	}

	//	빈칸이 없습니다
	if (x == -1)
	{	//	모든 빈칸을 채웠습니다.
		return 1;
	}

	//	각 모양에 맞춰서 블록을 놓습니다.
	for (int i = 0; i < 4; i++)
	{
		bool err = false;

		for (int t = 0; t < 3; t++)
		{
			int xx = 0;
			int yy = 0;
			xx = x + BlockType[i][t][0];
			yy = y + BlockType[i][t][1];
			//	일단 놓습니다
			if (xx < 0 || xx > width ||
				yy < 0 || yy > height)
			{	//	보드의 바깥입니다.
				err = true;
				continue;
			}
			board[yy][xx] += 1;
			int val = board[yy][xx];

			if (val > 1)
			{	//	겹쳐진 자리가 있습니다.
				err = true;
			}
		}

		if (!err)
		{	//	블록을 잘 놓았습니다.
			//	다음 블록을 놓습니다.
			retVal += SetBlock(board);
		}

		for (int t = 0; t < 3; t++)
		{	//	놓았던 블록을 들어냅니다.
			int xx = 0;
			int yy = 0;
			xx = x + BlockType[i][t][0];
			yy = y + BlockType[i][t][1];

			if (xx < 0 || xx > width ||
				yy < 0 || yy > height)
			{	//	보드의 바깥입니다.
				continue;
			}
			board[yy][xx] -= 1;
		}
	}

	//	블록 놓기가 끝났습니다.
	return retVal;
}