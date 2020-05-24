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

// Function to detect cycle in the given graph by using dfs. If there is a cycle then there will be a back edge
// We can also generate a cycle (if it exists) by keeping track of each vertex's parent node
bool has_cycle (vector<vector<int>> &graph, vector<bool> &visited, int vertex, int parent) {
    visited[vertex] = true;
    for (int child: graph[vertex]) {
        if (!visited[child]) {
            if (has_cycle (graph, visited, child, vertex) == true) {
                return true;
            }
        } else {
            if (child != parent) {
                return true;
            }
        }
    }
    return false;
}
