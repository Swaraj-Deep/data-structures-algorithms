#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// pair<int, int> a.first -> value and a.second -> weight
// first value of the pair is the value of the item and second value is the weight of the item
bool comp (pair<int,int> a, pair<int, int> b) {
  double r1 = (double)a.first / a.second;
  double r2 = (double)b.first / b.second;
  return r1 > r2;
}

double greedy_knapsack (vector<pair<int, int>>& items, int weight) {
  sort (items.begin (), items.end (), comp);
  int curr_weight = 0;
  double final_value = 0.0;
  for (int i = 0, len = items.size (); i < len; ++i) {
    if (curr_weight + items[i].second <= weight) {
      curr_weight += items[i].second;
      final_value += items[i].first;
    } else {
      int remain = weight - curr_weight;
      final_value += items[i].first * ((double) remain / items[i].second);
      break;
    }
  }
  return final_value;
}

