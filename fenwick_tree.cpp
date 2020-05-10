/*
    Fenwick Tree also called Binary Indexed Tree is a data structure which:
        calculates the value of function f in the given range [l,r] (i.e. f(Al,Al+1,…,Ar)) in O(logn) time;
        updates the value of an element of A in O(logn) time;
        requires O(N) memory, or in other words, exactly the same memory required for A;
        is easy to use and code, especially, in the case of multidimensional arrays.
    Zero Based indexing of the fenwick tree
*/

#include <iostream>
#include <vector>

using namespace std;

// Fenwick Tree for One Dimensional Array

// Function for point Update

void add(vector<int> &bit, int index, int value)
{
    for (int len = bit.size(); index < len; index = index | (index + 1))
    {
        bit[index] += value;
    }
}

// Function for building the BIT

void build_tree(vector<int> &bit, vector<int> &arr)
{
    for (int i = 0, len = arr.size(); i < len; ++i)
    {
        add(bit, i, arr[i]);
    }
}

// Function for range query

int query_helper(vector<int> &bit, int r)
{
    int res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1)
    {
        res += bit[r];
    }
    return res;
}

// Function for range query

int query_tree(vector<int> &bit, int l = 0, int r = 0)
{
    if (l == 0)
    {
        return query_helper(bit, r);
    }
    else
    {
        return query_helper(bit, r) - query_helper(bit, l - 1);
    }
}

// Range Update and Point Query

// Suppose we want to increment the interval [l, r] by x
// We make two point update operations on the BIT which are add (l, x) and add (r + 1, -x)
void range_update(vector<int> &bit, int l, int r, int value)
{
    add(bit, l, value);
    add(bit, r + 1, -value);
}

// Fenwick Tree for 2-D array

// Point Update for a Node in 2-D BIT

void add_2D(vector<vector<int>> &bit, int x, int y, int value)
{
    int n = bit.size();
    int m = bit[0].size();
    for (int i = x; i < n; i = i | (i + 1))
    {
        for (int j = y; j < m; j = j | (j + 1))
        {
            bit[i][j] += value;
        }
    }
}

// Build a 2-D BIT

void build_tree_2D(vector<vector<int>> &bit, vector<vector<int>> &arr)
{
    for (int i = 0, n = arr.size(); i < n; ++i)
    {
        for (int j = 0, m = arr[0].size(); j < m; ++j)
        {
            add_2D(bit, i, j, arr[i][j]);
        }
    }
}

// Range Query for a 2-D BIT

int query_tree_2D(vector<vector<int>> &bit, int x, int y)
{
    int res = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
    {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
        {
            res += bit[i][j];
        }
    }
    return res;
}