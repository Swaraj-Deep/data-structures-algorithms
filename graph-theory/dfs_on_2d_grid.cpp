/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool is_valid(int x, int y, vector<vector<bool>> &visited)
{
    int n = visited.size(), m = visited[0].size();
    if (x < 1 || x >= n || y < 1 || y >= m || visited[x][y])
    {
        return false;
    }
    return true;
}

vector<int> dx{-1, 0, 1, 0};
vector<int> dy{0, 1, 0, -1};

void dfs_on_grid(int x, int y, vector<vector<bool>> &visited)
{
    visited[x][y] = true;
    cout << x << ' ' << y << '\n';
    for (int i = 0; i < 4; ++i)
    {
        if (is_valid(x + dx[i], y + dy[i], visited))
        {
            dfs_on_grid(x + dx[i], y + dy[i], visited); // if the grid x + dx[i] and y + dy[i] is valid and not visited call dfs_on_grid
        }
    }
}
