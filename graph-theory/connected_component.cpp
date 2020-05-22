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

void dfs_search(vector<bool> &visited, vector<int> &component, int vertex, vector<vector<int>> &graph)
{
    visited[vertex] = true;
    component.push_back(vertex);
    for (size_t i = 0; i < (int)graph[vertex].size(); ++i)
    {
        int to = graph[vertex][i];
        if (!visited[to])
            dfs_search(visited, component, to, graph);
    }
}

void find_connected_components(int graph_size, vector<bool> &visited, vector<int> &component, vector<vector<int>> &graph)
{
    for (int i = 0; i < graph_size; ++i)
        visited[i] = false;
    for (int i = 0; i < graph_size; ++i)
        if (!visited[i])
        {
            component.clear();
            dfs_search(visited, component, i, graph);
            cout << "Component:";
            for (size_t j = 0; j < component.size(); ++j)
            {
                cout << ' ' << component[j];
            }
            cout << '\n';
        }
}