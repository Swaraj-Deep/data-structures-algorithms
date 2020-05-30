/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs_search(vector<vector<int>> &tree, vector<bool> &visited, int vertex, int dist, int &max_dist, int &max_node)
{
    visited[vertex] = true;
    if (dist > max_dist)
    {
        max_dist = dist;
        max_node = vertex;
    }
    for (int child : tree[vertex])
    {
        if (!visited[child])
        {
            dfs_search(tree, visited, child, dist + 1, max_dist, max_node);
        }
    }
}

// To get maximum distance we have to make two dfs calls
// 1 -> call to get the node with maxm distance from the passed root and in the
// 2 -> call we get the required diameter
int max_distance(vector<vector<int>> &tree, vector<bool> &visited, int vertex, int dist)
{
    int max_dist = -1;
    int max_node = -1;
    dfs_search(tree, visited, vertex, dist, max_dist, max_node);
    replace(visited.begin(), visited.end(), true, false);
    max_dist = -1;
    dfs_search(tree, visited, max_node, 0, max_dist, max_node);
    return max_dist;
}
