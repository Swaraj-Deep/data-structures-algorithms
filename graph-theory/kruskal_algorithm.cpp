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

// Structure to hold the edges and weight

struct edges
{
    pair<int, int> edge;
    int weight;
};

// Using path compression for finding parent

int find_set(int vertex, vector<int> &parent)
{
    return parent[vertex] < 0 ? vertex : parent[vertex] = find_set(parent[vertex], parent);
}

void union_sets(int parent_a, int parent_b, vector<int> &parent)
{
    parent[parent_b] = parent_a;
}

// Main function

int main()
{
    int a, b, weight, n, m;
    cin >> n >> m;                 // n -> Number of nodes, m - > Number of edges
    vector<edges> graph;           // vector to store graph information
    vector<int> parent(n + 1, -1); // Parent array for disjoint set
    while (m--)
    {
        cin >> a >> b >> weight;
        edges edge{{a, b}, weight};
        graph.push_back(edge);
    }
    // Sorting graph based on weight
    sort(graph.begin(), graph.end(), [](edges a, edges b) {
        return a.weight < b.weight;
    });
    int sum = 0;
    for (auto i : graph)
    {
        a = find_set(i.edge.first, parent);
        b = find_set(i.edge.second, parent);
        // if the parents are different then merge them to a single set
        if (a != b)
        {
            sum += i.weight; // Calculate the sum of the weights
            union_sets(a, b, parent);
        }
    }
    cout << sum << '\n';
    return 0;
}
