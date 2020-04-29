#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// all are variation of the knapsack problem 
bool is_subset_sum (vector<int>& nums, int target) {
  int len = nums.size ();
  vector<vector<int>> dp (len + 1, vector<int>(target + 1));
  for (int i = 0; i <= len; ++i) {
    for (int j = 0; j <= target; ++j) {
      if (i == 0) {
        dp[i][j] = false;
      }
      if (j == 0) {
        dp[i][j] = true;
      }
    }
  }
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= target; ++j) {
      if (nums[i] <= j) {
        dp[i][j] = dp[i - 1][j - nums[i]] || dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[len][target];
}

// Equal Sum Partition
bool equal_sum_partion (vector<int>& nums) {
  // check for the sum of elements in nums. if the sum turns out to be odd then there is no possible solution for equal sum partion else we just check for subset sum of sum / 2;
  int sum = 0;
  for (auto elem: nums) {
    sum += elem;
  }
  if (sum & 1) {
    return false;
  } else {
    return is_subset_sum (nums, sum / 2);
  }
}

int count_subset_sum (vector<int>& nums, int target) {
  int len = nums.size ();
  vector<vector<int>> dp (len + 1, vector<int>(target + 1));
  for (int i = 0; i <= len; ++i) {
    for (int j = 0; j <= target; ++j) {
      if (i == 0) {
        dp[i][j] = false;
      }
      if (j == 0) {
        dp[i][j] = true;
      }
    }
  }
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= target; ++j) {
      if (nums[i - 1] <= j) {
        dp[i][j] = dp[i - 1][j - nums[i - 1]] + dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  return dp[len][target];
}

int  minm_subset_sum_diff (vector<int>& nums) {
  // Let's there be two sum s1 and s2 now we have to minimize (s1 - s2)
  // now let the sum of all elements of the nums array be S then s1 = S - s2
  // i.e s2 - s1 => s2 - (S - s2) 
  // => s2 - S + s2 i.e 2s2 - S or S - 2s1
  // now we have to minimize S - 2s1
  // Not for -ve sums
  int len = nums.size ();
  int sum = 0;
  for (int i: nums) {
    sum += i;
  }
  vector<vector<int>> dp (len + 1, vector<int>(sum + 1));
  for (int i = 0; i <= len; ++i) {
    for (int j = 0; j <= sum; ++j) {
      if (i == 0) {
        dp[i][j] = false;
      }
      if (j == 0) {
        dp[i][j] = true;
      }
    }
  }
  for (int i = 1; i <= len; ++i) {
    for (int j = 1; j <= sum; ++j) {
      if (nums[i - 1] <= j) {
        dp[i][j] = dp[i - 1][j - nums[i - 1]] || dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }
  // We have to iterate through sum / 2 because to get rid of the redundant checks
  int ans = INT_MAX;
  for (int i = 0; i <= sum / 2; ++i) {
    if (dp[len][i]) {
      ans = min (ans, sum - 2 * i);
    }
  }
  return ans;
}

int number_of_subset_with_given_diff (vector<int>& nums, int diff) {
  // given an array find the number of different subsets which have a given diff
  // Maths
  // let the two subsets be s1 and s2
  // i.e. |s1 - s2| = diff ---- I
  // also sum (s1) + sum (s2) = sum of arrray -----II
  // adding I and II
  // 2 * sum (s1) = diff + sum (arr)
  // i.e. sum (s1) = (diff + sum (arr)) / 2 --- let's call this sum S'
  // we have to find the number of subsets having sum S'
  int sum = 0;
  for (int i: nums) {
    sum += i;
  }
  int S_prime = (diff + sum) / 2;
  return count_subset_sum (nums, S_prime);
}

