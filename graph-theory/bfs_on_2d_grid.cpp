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

// Function to check whether cell[x][y] is valid or not
bool is_valid(int x, int y, vector<vector<bool>> &visited)
{
    int n = visited.size(), m = visited.size();
    if (x < 1 || x >= n || y < 1 || y >= m || visited[x][y])
    {
        return false;
    }
    return true;
}

// Considering only adjacent cells as edges. Can also be extended for all eight cells
vector<int> dx{-1, 0, 1, 0};
vector<int> dy{0, 1, 0, -1};

void bfs_on_grid(int source_x, int source_y, vector<vector<bool>> &visited, vector<vector<int>> &distance)
{
    queue<pair<int, int>> q;
    q.push({source_x, source_y}); // Inserting into the queue the current cell
    visited[source_x][source_y] = true;
    distance[source_x][source_y] = 0; // Distance of source_x and source_y is zero
    while (!q.empty())
    {
        int current_x = q.front().first;
        int current_y = q.front().second;
        q.pop();
        // Checking all adjacent sides
        for (int i = 0; i < 4; ++i)
        {
            if (is_valid(current_x + dx[i], current_y + dy[i], visited))
            {
                int new_x = current_x + dx[i];
                int new_y = current_y + dy[i];
                distance[new_x][new_y] = distance[current_x][current_y] + 1;
                visited[new_x][new_y] = true;
                q.push({new_x, new_y});
            }
        }
    }
}
