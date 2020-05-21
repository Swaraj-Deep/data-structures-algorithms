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

// Function to make a dfs search to the passed graph
void dfs_search(vector<vector<int>> &graph, int vertex, vector<bool> &visited)
{
    visited[vertex] = true;     // Mark the current vertex as visited
    cout << vertex << ' ';      // Print the current vertex
    for (int u : graph[vertex]) // Iterate over each of the connected vertex of the given vertex
    {
        if (!visited[u]) // Check if the vertex is visited or not
        {
            dfs_search(graph, u, visited); // Make a dfs call if the current vertex is not visited
        }
    }
}