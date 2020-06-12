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

// Single Source Shortest Path in a weighted graph (Directed or Undirected)
int dijkstra_algorithm(int root, vector<vector<pi>> &graph, vector<int> &distance)
{
    // Priority queue to store the node and minimum cost to get up to there
    // first -> cost, second -> node
    // graph first -> node, second -> weight
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({0, root});
    distance[root] = 0;
    while (!pq.empty())
    {
        int parent = pq.top().second;
        int weight = pq.top().first;
        pq.pop();
        for (pi edge : graph[parent])
        {
            // Improve weight only if the cost is less than the previous cost
            if (weight + edge.second < distance[edge.first])
            {
                distance[edge.first] = weight + edge.second;
                pq.push({distance[edge.first], edge.first});
            }
        }
    }
}
