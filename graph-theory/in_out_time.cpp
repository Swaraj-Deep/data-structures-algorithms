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

// Function to generate the in and out time of the node using dfs
// This concept is used to determine whether two nodes lie in the same subtree or not
void dfs_in_out(vector<vector<int>> &graph, vector<bool> &visited, int vertex, int &timer, vector<int>&in, vector<int>&out )
{
    visited[vertex] = true;
    in[vertex] = timer++;
    for (int child: graph[vertex]) {
        if (!visited[child]) {
            dfs_in_out (graph, visited, child, timer, in, out);
        }
    }
    out[vertex] = timer++;
}
