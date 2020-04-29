#include <iostream>
#include <vector>

using namespace  std;

// pair<int, int> a.first -> value and a.second -> weight
int knapsack01 (vector<pair<int, int>>& items, int weight) {
  int len = items.size ();
  vector<vector<int>> dp (len + 1, vector<int>(weight + 1, 0));
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= weight; ++j) {
      if (items[i - 1].second <= j) {
        dp[i][j] = max (dp[i - 1][j - items[i - 1].second] + items[i - 1].first, dp[i - 1][j]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[len][weight];
}

int unbounded_knapsack (vector<pair<int, int>>& items, int weight) {
  int len = items.size ();
  vector<vector<int>> dp (len + 1, vector<int>(weight + 1, 0));
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= weight; ++j) {
      if (items[i - 1].second <= j) {
        dp[i][j] = max (dp[i][j - items[i - 1].second] + items[i - 1].first, dp[i - 1][j]);
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[len][weight];
}

// space optimized version of 0/1 knapsack 
// Here dp[i] will store the profit with knapsack capacity "i"
int knapsack01_space_optimized (vector<pair<int, int>>& items, int weight) {
  vector<int> dp (weight + 1, 0); // Initially all the profit is zero.
  for (int i = 0, len = items.size (); i < len; ++i) {
    // Traverse the dp array from left to right
    for (int j = weight; j>= items[i].second; j--) {
      dp[j] = max (dp[j], items[i].first + dp[j - items[i].second]); /* This line finds out the  maximum of dp[j] (excluding the ith element value) and items[i].fisrt + dp[j - items[i].second] (including the ith element value and the profit with knapsack capacity -ith element weight)*/ 
    }
  }
  return dp[weight];
}

// Space optimized unbounded knapsack
int unbounded_knapsack_space_optimized (vector<pair<int, int>>& items, int weight) {
  vector<int> dp (weight + 1, 0);
  for (int i = 0; i <= weight; ++i) {
    for (int j = 0, len = items.size (); j < len; ++j) {
      if (items[j].second <= i) {
        dp[i] = max (dp[i], dp[i - items[j].second] + items[j].first);
      }
    }
  }
  return dp[weight];
}

