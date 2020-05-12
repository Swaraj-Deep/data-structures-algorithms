#include <iostream>
#include <vector>

using namespace std;

vector<int> z_prefix (string s) {
    int n = s.size ();
    vector<int> z (n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min (r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

vector<int> z_search (string text, string pattern) {
    string new_str = pattern + "$" + text;
    int len_p = pattern.size ();
    vector<int> z = z_prefix (new_str);
    int len_z = z.size ();
    vector<int> pos;
    for (int i = len_p; i < len_z; ++i) {
        if (z[i] == len_p) {
            pos.push_back (i - len_p - 1);
        }
    }
    return pos;
}
