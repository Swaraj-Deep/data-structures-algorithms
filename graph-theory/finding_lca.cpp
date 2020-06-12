/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// DFS search for finding the depth and parent of each node in the graph
void dfs_search_naive(int vertex, vector<vector<int>> &graph, vector<bool> &visited, vector<int> &depth, vector<int> &parent, int d = 0, int par = -1)
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
            dfs_search_naive(child, graph, visited, depth, parent, d + 1, vertex);
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

// Normal DFS search
void dfs_search_optimized(int vertex, vector<vector<int>> &graph, vector<vector<int>> &parent, vector<int> &depth, int p = -1, int d = 0)
{
    parent[vertex][0] = p;
    depth[vertex] = d;
    for (int child : graph[vertex])
    {
        if (child != p)
        {
            dfs_search_optimized(child, graph, parent, depth, vertex, d + 1);
        }
    }
}

// Fill the parent array
void fill_parent_array(vector<vector<int>> &parent, int n)
{
    // For each column uptill log base 2(n)
    for (int j = 1; j <= log2(n); ++j)
    {
        // For each row
        for (int i = 1; i <= n; ++i)
        {
            // if the j - 1 th parent is -1 then we don't need to process it
            if (parent[i][j - 1] != -1)
            {
                // this equation holds as 2 ^ i = (2) * (2 ^ i - 1)
                parent[i][j] = parent[parent[i][j - 1]][j - 1];
            }
        }
    }
}

// Find the lowest common ancestor Time Complexity O(logN), Preprocessing time O(NlogN), Space complexity O(NlogN)
int lowest_common_ancestor_optimized(int a, int b, vector<vector<int>> &parent, vector<vector<int>> &graph, vector<int> &depth, int n)
{
    // Find the depth of both nodes
    if (depth[a] > depth[b])
    {
        swap(b, a);
    }
    int diff = abs(depth[b] - depth[a]);
    // Untill both the nodes are on the same level
    while (diff > 0)
    {
        int i = log2(diff);
        b = parent[b][i]; // make b point to point to its log2(diff)th parent rather than pointing to its immediate parent
        diff -= (1 << i);
    }
    // If both a and b are on the same chain return either a or b
    if (a == b)
    {
        return a;
    }
    // Both nodes are on different chain lift up the nodes by factor of log2(i) th parent rather than immediate parents
    for (int i = log2(n); i >= 0; --i)
    {
        if (parent[a][i] != -1 && (parent[a][i] != parent[b][i]))
        {
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}
