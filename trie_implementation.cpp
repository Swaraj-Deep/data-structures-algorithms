#include <iostream>
#define CHAR_SIZE 26

using namespace std;

class trie
{
    // Node Structure for a Trie
    struct trie_node
    {
        char val;                    // What is the value of that node
        int count;                   // How many node is with that value
        int ends_here;               // How many strings ends at that node
        trie_node *child[CHAR_SIZE]; // Array of pointers to hold the children CHAR_SIZE may vary. In this implementation it is only for lower case english alphabets
    };
    trie_node *root;               // Hold the root of the trie
    trie_node *get_node(int index) // Function to get the new node every time a child is created
    {
        trie_node *new_node = new trie_node;
        new_node->val = 'a' + index;               // Assign the value to the new_node
        new_node->count = new_node->ends_here = 0; // make count and ends_here equal to 0
        for (int i = 0; i < CHAR_SIZE; ++i)
        {
            new_node->child[i] = NULL; // Make all the child node NULL
        }
        return new_node; // Return the new_node
    }

public:
    trie()
    {
        root = get_node('/' - 'a'); // The root will store the forward slash in this implementation '/'
    }
    void insert(const string &);
    bool search(const string &);
    int starts_with(const string &);
    bool is_empty(const trie_node *);
    bool have_children(const trie_node *);
    trie_node* get_root () {
        return root;
    }
};

// Function to check is trie is empty or not
bool trie::is_empty(const trie_node *root)
{
    for (int i = 0; i < CHAR_SIZE; ++i)
    {
        if (root->child[i])
        {
            return false;
        }
    }
    return true;
}

// Function to check whether the trie have children or not
bool trie::have_children(const trie_node *root)
{
    return !is_empty(root);
}

// Function to insert in the trie
void trie::insert(const string &word)
{
    trie_node *current = root; // Point the current node to root pointer
    int index;
    for (int i = 0, len = word.size(); i < len; ++i)
    {
        index = word[i] - 'a';      // Get the index of the word
        if (!current->child[index]) // Check if the child is NULL or not
        {
            current->child[index] = get_node(index); // If Child is NULL then assign a new_node to it;
        }
        current->child[index]->count += 1; // Increment the current child count by 1
        current = current->child[index];   // Make the current pointer point to the current child
    }
    current->ends_here += 1; // Increment the current end_here by 1
}

// Function to search in the trie
bool trie::search(const string &word)
{
    trie_node *current = root; // Point the current node to root pointer
    int index;
    for (int i = 0, len = word.size(); i < len; ++i)
    {                          // Iterate over the word
        index = word[i] - 'a'; // Get the index of the word[i]
        if (!current->child[index])
        {                 // Check if there exists a child node of not
            return false; // if the child node doesn't exist then return false
        }
        current = current->child[index]; // Make the current pointer point to the current child
    }
    return (current->ends_here > 0); // Check if any string ends_here or not
}

// Function to check how many string are there with the given prefix
int trie::starts_with(const string &prefix)
{
    trie_node *current = root; // Point the current node to the root node
    int index;
    for (int i = 0, len = prefix.size(); i < len; ++i)
    {                            // Iterate over the whole prefix
        index = prefix[i] - 'a'; // Get the index of the current character of the prefix
        if (!current->child[index])
        {             // Check if there exists a child or not
            return 0; // if child doesn't exist return 0
        }
        current = current->child[index]; // Move the pointer to the next node
    }
    return current->count; // return the count at that node
}

int main()
{
    int n;
    string s;
    trie trie_root;
    cin >> n;
    while (getline(cin, s))
    {
        if (s == "-1")
        {
            break;
        }
        trie_root.insert(s);
    }
    while (n--)
    {
        getline(cin, s);
        cout << boolalpha << trie_root.search(s) << ' ';
        cout << trie_root.starts_with(s) << '\n';
    }
    cout << trie_root.have_children (trie_root.get_root ()) << '\n';
    return 0;
}