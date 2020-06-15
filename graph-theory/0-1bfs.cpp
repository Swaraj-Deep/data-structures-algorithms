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
#include <climits>
#define pi pair<int, int>

using namespace std;

// Single Source Shortest Path when weight is either zero or one
void zero_one_bfs(vector<vector<pi>> &graph, vector<int> &distance, int root, int dist = 0)
{
    distance[root] = dist;
    deque<int> dq; // Deque for storing nodes
    dq.push_front(root);
    while (!dq.empty())
    {
        int vertex = dq.front();
        dq.pop_front();
        for (pi child : graph[vertex])
        {
            int u = child.first;
            int w = child.second;
            // if adding this edge relaxes the previous cost then update it
            if (distance[vertex] + w < distance[u])
            {
                distance[u] = distance[vertex] + w;
                // Keep the nodes in sorted order i.e. if weight is one this node is one level down else it is at the same level
                if (w == 1)
                {
                    dq.push_back(u);
                }
                else
                {
                    dq.push_front(u);
                }
            }
        }
    }
}
