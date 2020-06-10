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

// Make set operation

void make_set(int vertex, vector<int> &parent, vector<int> &size, vector<int> &rank)
{
    parent[vertex] = -1; // -ve sign represents that it is parent and the magnitude represents the number of children that parent has.
    size[vertex] = 1;    // Size of the tree
    rank[vertex] = 0;    // Rank is the depth of the tree
}

// Find the parent of the given vertex without using path compression

int find_set(int vertex, vector<int> &parent)
{
    if (parent[vertex] < 0)
    {
        return vertex;
    }
    return find_set(parent[vertex], parent);
}

// Find the parent of the given vertex with path compression

int find_set_path_compression(int vertex, vector<int> &parent)
{
    if (parent[vertex] < 0)
    {
        return vertex;
    }
    return parent[vertex] = find_set_path_compression(parent[vertex], parent);
}

// Naive Union operation i.e merge two sets if they belongs to differnt sets this can lead to trees containing chains of length O(N)

void union_sets(int parent_a, int parent_b, vector<int> &parent)
{
    parent_a = find_set_path_compression(parent_a, parent);
    parent_b = find_set_path_compression(parent_b, parent);
    if (parent_a != parent_b)
    {
        parent[parent_a] += parent[parent_b]; // Add the number of child which the parent of other child had.
        parent[parent_b] = parent_a;          // Make the parent of one set point to other
    }
}

// Union operation based on size

void union_sets_size(int parent_a, int parent_b, vector<int> &parent, vector<int> &size)
{
    parent_a = find_set_path_compression(parent_a, parent);
    parent_b = find_set_path_compression(parent_b, parent);
    if (parent_a != parent_b)
    {
        if (size[parent_a] < size[parent_b])
        {
            swap(parent_a, parent_b);
        }
        parent[parent_a] += parent[parent_b];
        parent[parent_b] = parent_a;
        size[parent_a] += size[parent_b];
    }
}

// Union based on rank i.e. depth of the trees

void union_sets_rank(int parent_a, int parent_b, vector<int> &parent, vector<int> &rank)
{
    parent_a = find_set_path_compression(parent_a, parent);
    parent_b = find_set_path_compression(parent_b, parent);
    if (parent_a != parent_b)
    {
        if (rank[parent_a] < rank[parent_b])
        {
            swap(parent_a, parent_b);
        }
        parent[parent_a] += parent[parent_b];
        parent[parent_b] = parent_a;
        if (rank[parent_a] == rank[parent_b])
        {
            rank[parent_a]++;
        }
    }
}
