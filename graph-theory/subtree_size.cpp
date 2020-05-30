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

// Without returning int
void dfs_search(vector<vector<int>> &tree, vector<bool> &visited, int vertex, vector<int> &subtree_size)
{
    visited[vertex] = true;
    int curr_size = 1;
    for (int child : tree[vertex])
    {
        if (!visited[child])
        {
            dfs_search(tree, visited, child, subtree_size);
            curr_size += subtree_size[child];
        }
    }
    subtree_size[vertex] = curr_size;
}

// With returning int
int dfs_search_int(vector<vector<int>> &tree, vector<bool> &visited, int vertex, vector<int> &subtree_size)
{
    visited[vertex] = true;
    int curr_size = 1;
    for (int child : tree[vertex])
    {
        if (!visited[child])
        {
            curr_size += dfs_search_int(tree, visited, child, subtree_size);
        }
    }
    subtree_size[vertex] = curr_size;
    return curr_size;
}
