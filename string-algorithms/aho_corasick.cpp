/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

/*
    Preprocessing: Build an automaton of all words in the given dictionary. The automaton has three functions.
    1. go_to:       This function simply follows edges
                    of Trie of all words in dict[]. It is
                    represented as 2D array g[][] where
                    we store next state for current state 
                    and character.

    2. failure:     This function stores all edges that are
                    followed when current character doesn't
                    have edge in Trie.  It is represented as
                    1D array f[] where we store next state for
                    current state. 

    3. output :     Stores indexes of all words that end at 
                    current state. It is represented as 1D 
                    array o[] where we store indexes
                    of all matching words as a bitmap for 
                    current state.
*/

#include <iostream>
#include <vector>
#include <queue>
#define MAXS 250 // Sum of length of all the string in the given dictionary of words
#define MAXC 26  // Size of alphabet

using namespace std;

vector<int> out(MAXS, 0);                           // This array is used by the output function. Bit i in this mask is one of the word with index i.
vector<int> f(MAXS, -1);                            // This array is used by the failure function.
vector<vector<int>> g(MAXS, vector<int>(MAXC, -1)); // This array is used by the go_to function

// Build the string matching automaton
// dict -> the array of string
// returns number of states build automaton has where states start from 0
int build_matching_automaton(const vector<string> &dict)
{
    int states = 1; // Initially we have just 0 state.
    // Build the trie of words in dict
    int i = 0;
    for (string word : dict)
    {
        int current_state = 0;
        for (char ch : word)
        {
            ch = ch - 'a';
            // Allocate a new node if node for ch doesn't exist
            if (g[current_state][ch] == -1)
            {
                g[current_state][ch] = states++;
            }
            current_state = g[current_state][ch];
        }
        // Add current word in output function
        out[current_state] |= (1 << i++);
    }
    // For all characters which don't have an edge from root (or state 0) in TRIE, add a go_to edge to state 0 itself
    for (int ch = 0; ch < MAXC; ++ch)
    {
        if (g[0][ch] == -1)
        {
            g[0][ch] = 0;
        }
    }
    // build the failure links
    queue<int> q;
    for (int ch = 0; ch < MAXC; ++ch)
    {
        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }
    while (!q.empty())
    {
        // remove the front state from queue
        int state = q.front();
        q.pop();
        for (int ch = 0; ch < MAXC; ++ch)
        {
            if (g[state][ch] != -1)
            {
                int failure = f[state];
                while (g[failure][ch] == -1)
                {
                    failure = f[failure];
                }
                failure = g[failure][ch];
                f[g[state][ch]] = failure;
                out[g[state][ch]] |= out[failure];
                q.push(g[state][ch]);
            }
        }
    }
    return states;
}

// Returns the next state the machine will transition to using goto
// and failure functions.
// current_state -  The current state of the machine. Must be between
//                  0 and the number of states - 1, inclusive.
// next_input -     The next character that enters into the machine.
int find_next_state(int current_state, char next_input)
{
    int answer = current_state;
    int ch = next_input - 'a';
    // If goto is not defined, use failure function
    while (g[answer][ch] == -1)
    {
        answer = f[answer];
    }
    return g[answer][ch];
}

// This function finds all occurrences of all array words in text.
void search_words(const vector<string> &dict, string text)
{
    // Preprocess patterns.
    // Build machine with goto, failure and output functions
    build_matching_automaton(dict);
    // Initialize current state
    int current_state = 0;
    // Traverse the text through the nuilt machine to find all occurrences of words in dict[]
    for (int i = 0; i < text.size(); ++i)
    {
        current_state = find_next_state(current_state, text[i]);
        // If match not found, move to next state
        if (out[current_state] == 0)
        {
            continue;
        }
        // Match found, print all matching words of dict[] using output function.
        for (int j = 0, len = dict.size(); j < len; ++j)
        {
            if (out[current_state] & (1 << j))
            {
                cout << "Word " << dict[j] << " appears from " << i - dict[j].size() + 1 << " to " << i << endl;
            }
        }
    }
}
