//	외판원 문제.
#include "Salesman.h"

#include <vector>


int g_Cities;
float g_Dist[MAX_CITIES][MAX_CITIES];

float FindShortestPath(int numberOfCities, float distance[MAX_CITIES][MAX_CITIES])
{	//	각 도시를 모두 방문하는 최단거리를 구했을 때 그 거리를 반환한다.

	//	numberOfCities to g_Cities
	//	distance to g_Dist

}


//	path : 도시들을 방문한 순서
//	visited : 도시의 방문 여부
//	currentLengh : 현재까지 경로의 길이
float ShortestPath(std::vector<int>& path, std::vector<bool> visited, float currentLength)
{
	if (path.size() == g_Cities)
	{	//	모든 도시를 방문했습니다.
		//	시작점으로 돌아옵니다.
		float dist = g_Dist[path[0]][path.back()];
		return dist;
	}

	//	충분히 큰 값
	float ret = INFINITY;

	//	다음 방문할 도시를 모두 방문해보도록 한다.
	for (int next = 0; next < g_Cities; next++)
	{
		if (visited[next] != 0)
		{	//	이미 방문한 도시입니다.
			continue;
		}


	}

}