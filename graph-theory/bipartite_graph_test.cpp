/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

// Bipartite graph test or two coloring test using dfs calls
#include <iostream>
#include <vector>

using namespace std;

bool is_bipartitie_graph(vector<vector<int>> &graph, int vertex, vector<bool> &visited, vector<int> &color, int col)
{
    visited[vertex] = true;
    color[vertex] = col;
    for (int child: graph[vertex]) {
        if (!visited[child]) {
            if (is_bipartitie_graph (graph, child, visited, color, col ^ 1) == false) {
                return false;
            }
        } else {
            if (color[vertex] == color[child]) {
                return false;
            }
        }
    }
    return true;
}
