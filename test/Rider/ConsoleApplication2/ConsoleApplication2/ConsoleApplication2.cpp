#include <iostream>
using namespace std;

int grp[101][101];
int vis[101];
int n;
int x, y;
int length;

int dfs(int root)
{
    if (vis[root] == 1) return 0;
    if (root == y) return 1;
    vis[root] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (grp[root][i])
        {
            length += dfs(i);
            if(length > 0)
            {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    cin >> n;
    cin >> x >> y;
    int m ;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        grp[a][b] = 1;
        grp[b][a] = 1;
    }
    dfs(x);
    if (length == 0)    length = -1;
    cout << length << endl;
}
