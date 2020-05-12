#include <iostream>
#include <vector>

using namespace std;

// Function to store z values of a given string
// i.e. z[i] is the length of the longest common prefix between s and the suffix of s starting at i
vector<int> z_prefix(string s)
{
    int n = s.size();
    vector<int> z(n); // Array to store the z indices of the string
    for (int i = 1, l = 0, r = 0; i < n; ++i)
    {
        // check that the current index is in the z box
        if (i <= r)
        {
            z[i] = min(r - i + 1, z[i - l]);
        }
        // if s[z[i]] matches s[i + z[i]] then increment the z[i] value
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
        {
            ++z[i];
        }
        // if adding value to the current index overpass z box then update l and r of hte z box
        if (i + z[i] - 1 > r)
        {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

// Search the given pattern in the text
vector<int> z_search(string text, string pattern)
{
    string new_str = pattern + "$" + text; // Concatenate both the string by a string which is not in both the string
    int len_p = pattern.size();            // we can start from here
    vector<int> z = z_prefix(new_str);     // get the z array for the new string i.e. concatenated string
    int len_z = z.size();
    vector<int> pos;
    for (int i = len_p; i < len_z; ++i)
    {
        if (z[i] == len_p)
        {
            pos.push_back(i - len_p - 1); // Insert the position of occurences of  the pattern in the text
        }
    }
    return pos;
}
