
#include <iostream>
#include <string>
using namespace std;

int n, m;
int a[101][101];
int visited[101][101];

int dy[4] = { -1 , 0 , 1 ,0 };
int dx[4] = { 0,1,0,-1 };

void dfs(int y, int x, int height)
{
    visited[y][x] = true;
    
    for (int i = 0; i < 4; i++)
    {
        int ny = y + dy[i];
        int nx = x + dx[i];
        
        if (0 > ny || 0 > nx || ny >= n || nx >= n) continue;
        if (visited[ny][nx] || a[ny][nx] <= height) continue;
        
        dfs(ny, nx, height);
    }
}

int main()
{
    cin >> n;
    int maxheight = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
            maxheight = max(maxheight, a[i][j]);
        }
    }
    
    int landmax = 0;
    int height = 0;
    
    while (maxheight--)
    {
        memset(visited, 0, sizeof(visited));
        int land = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (visited[i][j] == 0 && a[i][j] > height)
                {
                    dfs(i, j, height);
                    land++;
                }
            }
        }
        landmax = max(landmax, land);
        height++;
    }
    
    cout << landmax;
    
    return 0;
}