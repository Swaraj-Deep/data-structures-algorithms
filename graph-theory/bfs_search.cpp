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

void bfs_search(vector<vector<int>> &graph, vector<bool> &visited, int root_vertex)
{
    visited[root_vertex] = true;
    queue<int> q;
    q.push(root_vertex);
    while (!q.empty())
    {
        int parent = q.front();
        q.pop();
        cout << parent << " -> ";
        for (int child : graph[parent])
        {
            if (!visited[child])
            {
                visited[child] = true;
                q.push(child);
            }
        }
    }
}
