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

// DFS search for finding the depth and parent of each node in the graph
void dfs_search(int vertex, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &depth, vector<int> &parent, int d = 0, int par = -1)
{
    visited[vertex] = true;
    depth[vertex] = d;    // Making the depth as d
    parent[vertex] = par; // Making the parent of vertex as par
    // Iterating over all neighbours of the current vertex
    for (int child : graph[vertex])
    {
        // if the neighbour is not visited make a dfs_call
        if (!visited[child])
        {
            // parent for this will be vertex and depth will be one more than the previous value
            dfs_search(child, graph, visited, depth, parent, d + 1, vertex);
        }
    }
}

// Naive method for lowest common ancestor Time Complexity: O(N) Space Complexity: O(N)
int lowest_common_ancestor(int a, int b, vector<int> &parent, vector<int> &depth)
{
    // Calculate depth of both node
    int d_1 = depth[a];
    int d_2 = depth[b];
    if (d_1 > d_2)
    {
        swap(b, a);
    }
    // Calculate the absolute difference of the depths
    int diff = abs(d_1 - d_2);
    while (diff > 0)
    {
        // Lift node b until both nodes a and b are on the same level
        b = parent[b];
        diff--;
    }
    // if both nodes collide then they belong to the same chain return any value
    if (a == b)
    {
        return a;
    }
    // while the parent of both the nodes are not same lift both nodes simultaneously
    while (parent[a] != parent[b])
    {
        a = parent[a];
        b = parent[b];
    }
    return parent[a];
}
