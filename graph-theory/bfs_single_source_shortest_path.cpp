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

void bfs_search(vector<vector<int>> &graph, vector<bool> visited, int root_vertex, vector<int> &distance)
{
    queue<int> q;
    q.push(root_vertex);
    distance[root_vertex] = 0;
    visited[root_vertex] = true;
    while (!q.empty())
    {
        int parent = q.front();
        q.pop();
        for (int child : graph[parent])
        {
            if (!visited[child])
            {
                visited[child] = true;
                q.push(child);
                distance[child] = distance[parent] + 1;
            }
        }
    }
}
