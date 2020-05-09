/*
    Segment Tree implementation for minimum in a given range.
    The indexing is 1 based for zero based indexing left child will be (2 * i + 1) and right child will be (2 * i + 2)
    Upper bound for memory needs of segment tree implemented through arrays is 4 * n + 1 for one based indexing or 4 * n for zero based indexing
    Number of nodes in a segment tree is 2 * 2 ^ x + 1 (here x is ceil value of log base 2 n)
    Time Complexities:
    Build Tree O(N)
    Query Tree O(log N)
    Point Update Tree O(log N)
    Range Update Tree O(N)
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

void build_tree(vector<int> &tree, vector<int> &arr, int index, int start, int end)
{
    if (start == end)
    {
        tree[index] = arr[start];
        return;
    }
    int mid = start + ((end - start) / 2);
    build_tree(tree, arr, 2 * index, start, mid);
    build_tree(tree, arr, 2 * index + 1, mid + 1, end);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
}

int query_tree(vector<int> &tree, int index, int segment_start, int segment_end, int q_start, int q_end)
{
    // Query range lies completely outside
    if (q_start > segment_end || q_end < segment_start)
    {
        return INT_MAX;
    }
    // Query range lies completely inside
    if (segment_start >= q_start && segment_end <= q_end)
    {
        return tree[index];
    }
    // Overlapping range query
    int mid = segment_start + ((segment_end - segment_start) / 2);
    int left_ans = query_tree(tree, 2 * index, segment_start, mid, q_start, q_end);
    int right_ans = query_tree(tree, 2 * index + 1, mid + 1, segment_end, q_start, q_end);
    return min(left_ans, right_ans);
}

void point_update_tree(vector<int> &tree, int index, int start, int end, int update_index, int value)
{
    // No overlap
    if (update_index < start || update_index > end)
    {
        return;
    }
    // Reached Leaf Node of the tree
    if (start == end)
    {
        tree[index] = value;
        return;
    }
    // Partial Overlap Calling both sides of the tree
    int mid = start + ((end - start) / 2);
    point_update_tree(tree, 2 * index, start, mid, update_index, value);
    point_update_tree(tree, 2 * index + 1, mid + 1, end, update_index, value);
    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return;
}

void range_update_tree(vector<int> &tree, int index, int start, int end, int r_start, int r_end, int value)
{
    // No overlap
    if (r_end < start || r_start > end) {
        return;
    }
    // Reached Leaf Node
    if (start == end){
        tree[index] = value;
        return;
    }
    // Partial Overlap
    int mid = start + ((end - start) / 2);
    range_update_tree (tree, 2 * index, start, mid, r_start, r_end, value);
    range_update_tree (tree, 2 * index + 1, mid + 1, end, r_start, r_end, value);
    tree[index] = min (tree[2 * index], tree[2 * index + 1]);
    return;
}
