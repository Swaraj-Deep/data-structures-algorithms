/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Assumption that the Graph is Directed Acyclic Graph ie. it doesn't contains any cycles.
void topological_sort(vector<vector<int>> &graph, vector<int> &in_degree, vector<int> &result)
{
    queue<int> q;
    for (int i = 1, n = in_degree.size(); i < n; ++i)
    {
        if (!in_degree[i])
        {
            q.push(i); // If in_degree of the node is zero then push it to the queue.
        }
    }
    while (!q.empty())
    {
        int current_node = q.front();   // Get the current node
        result.push_back(current_node); // Push it to the result
        q.pop();
        for (int node : graph[current_node]) // Check for each neighbour of the current_node
        {
            in_degree[node]--; // Remove the edge
            if (!in_degree[node])
            {
                q.push(node); // if in_degree is zero then push it to queue
            }
        }
    }
}
