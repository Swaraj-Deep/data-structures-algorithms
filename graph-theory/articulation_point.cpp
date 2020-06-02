/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void add_articulation_vertex(int vertex, set<int> &vertices)
{
    vertices.insert(vertex);
}

void dfs_search(vector<vector<int>> &graph, vector<bool> &visited, int vertex, int root, int timer, vector<int> &in_time, vector<int> &low_time, set<int> &vertices)
{
    visited[vertex] = true;
    in_time[vertex] = low_time[vertex] = timer++;
    int children = 0;
    for (int child : graph[vertex])
    {
        if (child == root)
        {
            continue;
        }
        if (visited[child])
        {
            // edge vertex -> child is a back edge so just minimize low_time
            low_time[vertex] = min(low_time[vertex], in_time[child]);
        }
        else
        {
            // edge vertex -> child is a forward edge
            dfs_search(graph, visited, child, vertex, timer, in_time, low_time, vertices);
            if (low_time[child] >= in_time[vertex] && root != -1)
            {
                add_articulation_vertex(vertex, vertices);
            }
            // minimize the low_time of the vertex
            low_time[vertex] = min(low_time[vertex], low_time[child]);
            ++children;
        }
    }
    // Check whether the root is an articulation point or not
    if (root == -1 && children > 1)
    {
        add_articulation_vertex(vertex, vertices);
    }
}

