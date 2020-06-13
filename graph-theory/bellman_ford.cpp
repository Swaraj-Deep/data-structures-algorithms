/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Structure to store the information about the edge and the weight
struct edge
{
    int to, from, weight;
};

// Simple bellman ford algorithm
void bellman_ford(int root, vector<edge> &graph, vector<int> &distance, int vertices, int edges, int d = 0)
{
    distance[root] = d;
    for (int i = 1; i <= vertices; ++i)
    {
        // Relax all distances for number of vertices times
        for (int j = 0; j < edges; ++j)
        {
            if (distance[graph[j].to] < INT_MAX)
            {
                // Relax the distance
                distance[graph[j].from] = min(distance[graph[j].from], distance[graph[j].to] + graph[j].weight);
            }
        }
    }
}

// Enhanced Bellman ford algorithm however it doesnot improve the asymptotic behaviour of the algorithm
void bellman_ford_enhanced(int root, vector<edge> &graph, vector<int> &distance, int vertices, int edges, int d = 0)
{
    distance[root] = d;
    for (;;)
    {
        bool any_change = false;
        for (int i = 1; i <= vertices; ++i)
        {
            for (int j = 0; j < edges; ++j)
            {
                if (distance[graph[j].to] < INT_MAX)
                {
                    if (distance[graph[j].from] > distance[graph[j].to] + graph[j].weight)
                    {
                        // Relax the distances
                        distance[graph[j].from] = distance[graph[j].to] + graph[j].weight;
                        any_change = true;
                    }
                }
            }
        }
        // If we cannot perform any relaxtion break the loop
        if (!any_change)
        {
            break;
        }
    }
}

// Bellman ford algorithm to actually generate the shortest path using the parent vector
void bellman_ford_path_enhanced(int root, vector<edge> &graph, vector<int> &distance, int vertices, int edges, vector<int> &parent, int d = 0)
{
    distance[root] = d;
    for (;;)
    {
        bool any_change = false;
        for (int i = 1; i <= vertices; ++i)
        {
            for (int j = 0; j < edges; ++j)
            {
                if (distance[graph[j].to] < INT_MAX)
                {
                    if (distance[graph[j].from] > distance[graph[j].to] + graph[j].weight)
                    {
                        distance[graph[j].from] = distance[graph[j].to] + graph[j].weight;
                        parent[graph[j].from] = graph[j].to;
                        any_change = true;
                    }
                }
            }
        }
        if (!any_change)
        {
            break;
        }
    }
}

// Detect negative cycles in the graph
void bellman_ford_negative_cycle(int root, vector<edge> &graph, vector<int> &distance, vector<int> &parent, int vertices, int edges, int d = 0)
{
    distance[root] = d;
    int x;
    for (int i = 1; i <= vertices; ++i)
    {
        x = -1;
        for (int j = 0; j < edges; ++j)
            if (distance[graph[j].to] < INT_MAX)
                if (distance[graph[j].from] > distance[graph[j].to] + graph[j].weight)
                {
                    distance[graph[j].from] = max(INT_MIN, distance[graph[j].to] + graph[j].weight);
                    parent[graph[j].from] = graph[j].to;
                    x = graph[j].from;
                }
    }
    if (x == -1)
    {
        cout << "No negative cycle from " << root << '\n';
    }
    else
    {
        int y = x;
        for (int i = 1; i <= vertices; ++i)
        {
            y = parent[y];
        }
        vector<int> cycle;
        for (int cur = y;; cur = parent[cur])
        {
            cycle.push_back(cur);
            if (cur == y && cycle.size() > 1)
                break;
        }
        cout << "Negative cycle: ";
        for (auto itr = cycle.rbegin(); itr != cycle.rend(); ++itr)
        {
            cout << *itr << ' ';
        }
        cout << '\n';
    }
}
