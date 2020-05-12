#include <iostream>
#include <vector>

using namespace std;

// KMP Prefix function i.e. it computes the longest common prefix vector of a given pattern
vector<int> kmp_prefix(string pattern)
{
    int n = pattern.size();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i)
    {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j])
        {
            j++;
        }
        pi[i] = j;
    }
    return pi;
}

// Function to check whether the substring occurs in the function or not
vector<int> kmp_search(string pattern, string text)
{
    vector<int> pi = kmp_prefix(pattern);
    int i = 0; // index for text
    int j = 0; // index for pattern
    int len = text.size();
    int len_p = pattern.size();
    vector<int> pos;
    while (i < len)
    {
        // We got a match here so we increment both i and j
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        // j is equal to pattern length i.e. found a match in the text
        if (j == len_p)
        {
            // We insert the position of the starting index of the pattern in the vector of positions
            pos.push_back(i - j);
            // Readjusting the j
            j = pi[j - 1];
        }
        else if (pattern[j] != text[i]) // The pattern and text doesnot matches so adjust the j pointer
        {
            // check if j is already 0 if yes then increment i else point it to pi[j - 1]
            if (j != 0)
            {
                j = pi[j - 1];
            }
            else
            {
                i++;
            }
        }
    }
    return pos;
}
