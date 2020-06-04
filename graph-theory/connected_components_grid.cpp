/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>

using namespace std;

/*
Sample input graph (is_valid function needs to be changed as per input)
0 0 1 0 1 1
0 1 1 0 0 1
0 1 0 0 0 0
1 0 1 1 0 0
0 0 0 1 0 0
0 1 1 0 1 1
*/

// Check if the cell is valid
bool is_valid(int x, int y, vector<vector<bool>> &visited, vector<vector<int>> &grid)
{
    int n = visited.size(), m = visited[0].size();
    if (x < 1 || x >= n || y < 1 || y >= m || visited[x][y] || !grid[x][y])
    {
        return false;
    }
    return true;
}

// vectors for movement
vector<int> dx{-1, 0, 1, 0};
vector<int> dy{0, 1, 0, -1};

void dfs_grid(int x, int y, vector<vector<bool>> &visited, vector<vector<int>> &grid)
{
    visited[x][y] = true;
    for (int i = 0; i < 4; ++i)
    {
        if (is_valid(x + dx[i], y + dy[i], visited, grid))
        {
            dfs_grid(x + dx[i], y + dy[i], visited, grid); // make a dfs call is every thing is fine
        }
    }
}

int count_connected_components(vector<vector<int>> &grid)
{
    int n = grid.size() - 1, m = grid[0].size() - 1, connected_components = 0;
    vector<vector<bool>> visited(n + 1, vector<bool>(m + 1, false));
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            if (grid[i][j] == 1 && !visited[i][j])
            {
                connected_components++;
                dfs_grid(i, j, visited, grid);
            }
        }
    }
    return connected_components; // Return the connected components
}
