#include <iostream>
#include <functional>
#include <algorithm>
#include <math.h>
#include <ctype.h>
#include <vector>
#include <regex>
#include <locale>
#include <stack>
#include <queue>
#include <bitset>
#include <map>
#include <iterator>
#include <set>
#include <climits>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#define FASTIO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define INF 1e9 + 5
#define MOD 1000000007

using u64 = uint64_t;
using u128 = __uint128_t;
using namespace std;

void leftrotate(string &s, int d) {
    reverse(s.begin(), s.begin()+d);
    reverse(s.begin()+d, s.end());
    reverse(s.begin(), s.end());
}

void rightrotate(string &s, int d) {
    leftrotate(s, s.length()-d);
}

std::string ltrim(const std::string& s) {
	return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
}

std::string rtrim(const std::string& s) {
	return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
}

std::string trim(const std::string& s) {
	return ltrim(rtrim(s));
}

void helper (ll A, string& result) {
	if (A > 1)
        helper (A / 2, result);
    result += to_string (A % 2);
}

string dec_to_bin (ll A) {
    string result;
    helper (A, result);
    return result;
}

void print_intmatrix_vector (vector<vector<int>> &mat) {
    for_each (mat.begin (), mat.end (), [](auto x) {for_each (x.begin (), x.end (), [](int x){cout << x << ' ';});cout << '\n';});
    cout << '\n';
}

void print_int_vector (vector<int> &vec) {
    for_each (vec.begin (), vec.end (), [](int x){cout << x << ' ';});
    cout << '\n';
}

void replace (string &s, const char search, const char key) {
    replace(s.begin(), s.end(), search, key);
}

void int_vector_to_string (vector<int>& vec, string& ans, int start = 0, int end = 0) {
    for_each (vec.begin () + start, vec.end () - end, [&ans](int x){ans += to_string (x);});
}

string multiply (string a, string b) {
    int a_len = a.size (), b_len = b.size ();
    vector<int> vals((a_len + b_len + 1), 0);
    for (int i = b_len - 1; i >= 0; --i) {
        for (int j = a_len - 1; j >= 0; --j) {
            int num1 = b[i] - '0', num2 = a[j] - '0';
            int mul = num1 * num2;
            if (mul > 9) {
                vals[i + j + 1] += mul % 10;
                vals[i + j ] += mul / 10;
            } else {
                vals[i + j + 1] += mul;
            }
            if (vals[i + j + 1] > 9) {
                mul = vals[i + j + 1];
                vals[i + j + 1] = mul % 10;
                vals[i + j] += mul / 10;
            }
        }
    }
    int i = 0;
    while (vals[i] == 0) {
        i++;
    }
    string ans = "";
    int_vector_to_string (vals, ans, i, 1);
    return ans;
}

int get_first_negative (vector<int>& vt) {
    int low = 0, high = vt.size () - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (vt[mid] < 0 && vt[max (mid - 1, 0)] >= 0) {
            return mid;
        } else if (vt[mid] >= 0) {
            low = mid + 1;
        } else if (vt[max (mid - 1, 0)] < 0) {
            high = mid - 1;
        }
    }
    return -1;
}

int get_first_zero (vector<int>& vt) {
    int low = 0, high = vt.size () - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (vt[mid] == 0 && vt[max (mid - 1, 0)]  == 1) {
            return mid;
        } else if (vt[mid] == 1) {
            low = mid + 1;
        } else if (vt[mid] == 0) {
            high = mid - 1;
        }
    }
    return -1;
}

bool is_prime_naive (ll n) {
  if (n == 1) {
    return false;
  }
  for (int i = 2; i < n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

bool  is_prime_better (ll n) {
  if (n == 1) {
    return false;
  }
  for (int i = 2; i * i < n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }
  return true;
}

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool probably_prime_fermat(ll n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    for (int i = 0; i < iter; i++) {
        ll a = 2 + rand() % (n - 3);
        if (binpower(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool miller_rabin(u64 n, int iter=5) {
    if (n < 4)
        return n == 2 || n == 3;

    int s = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < iter; i++) {
        int a = 2 + rand() % (n - 3);
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}

bool miller_rabin_deterministic(u64 n) {
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

