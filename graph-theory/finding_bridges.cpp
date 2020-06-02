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

// Observation from the DFS tree
// Backedge is an edge which connects the node to its ancestor which is not its direct parent
// Backedge can never be a bridge
void dfs_search(vector<vector<int>> &graph, vector<bool> &visited, int vertex, int parent, int &timer, vector<int> &in_time, vector<int> &low_time)
{
    visited[vertex] = true;
    low_time[vertex] = in_time[vertex] = timer++;
    for (int child : graph[vertex])
    {
        if (child == parent)
        {
            continue;
        }
        if (!visited[child])
        {
            // egde vertex -> child is a forward edge so we have to check for bridges
            dfs_search(graph, visited, child, vertex, timer, in_time, low_time);
            if (low_time[child] > in_time[vertex])
            {
                cout << vertex << " -> " << child << " is a bridge.\n";
            }
            low_time[vertex] = min(low_time[vertex], low_time[child]);
        }
        else
        {
            // edge vertex -> child is a backward edge so we don't need to check for bridges
            low_time[vertex] = min(low_time[vertex], in_time[child]);
        }
    }
}
