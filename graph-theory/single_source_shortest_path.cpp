/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/
// Single Source Shortest Path on trees

#include <iostream>
#include <vector>

using namespace std;

void dfs_search(vector<vector<int>> &graph, int vertex, vector<bool> &visited, int dist, vector<int> &s_distance)
{
    visited[vertex] = true;
    s_distance[vertex] = dist;
    for (int u : graph[vertex])
    {
        if (!visited[u])
        {
            dfs_search(graph, u, visited, s_distance[vertex] + 1, s_distance);
        }
    }
}
