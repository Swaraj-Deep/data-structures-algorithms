/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <exception>

using namespace std;

template <typename T>
struct node
{                // structure of a node in the BST
    T data;      // Data field of the node
    node *left;  // Address of the left child
    node *right; // Address of the right child
};

template <typename T>
class BST
{ // BST Class
private:
    int len;                               // Keeps track of current number of elements in the BST
    node<T> *root;                         // stores the root node of the BST
    node<T> *get_new_node(const T &);      // get the new node for the BST
    void remove_all(node<T> *);            // Remove all the nodes from the BST
    node<T> *insert(node<T> *, const T &); // helper to insert the node to the BST
    node<T> *search(node<T> *, const T &); // helper to search for the data in BST
public:
    BST();                                 // Constructor of the BST
    ~BST();                                // Destructor of the BST
    int get_length();                      // Get the length of the BST
    void add(const T &);                   // Add the given element to the BST
    node<T> *find(const T &);              // Check whether the given element is present in the BST or not
    node<T> *get_root();                   // get the root of the BST
    bool remove(const T &);                // Remove a given node from the BST
    void print_preorder(node<T> *);        // Prints the preorder of the BST
    void print_inorder(node<T> *);         // Prints the inorder of the BST
    void print_postorder(node<T> *);       // Prints the postorder of the BST
    void print_levelorder(node<T> *);      // Prints the levelorder of the BST
    node<T> *inorder_successor(node<T> *); // Returns the reference to the inorder successor of the given node roference
    node<T> *find_min(node<T> *);          // Returns the reference to the minimum element in the passed reference
    node<T> *find_max(node<T> *);          // Returns the reference to the maxm element in the passed reference
};

template <typename T>
BST<T>::BST()
{
    this->len = 0;
    this->root = NULL;
}

template <typename T>
node<T> *BST<T>::get_new_node(const T &data)
{
    node<T> *new_node = new node<T>;
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

template <typename T>
BST<T>::~BST()
{
    remove_all(this->root);
}

template <typename T>
int BST<T>::get_length()
{
    return this->len; // Get the length of the BST
}

template <typename T>
node<T> *BST<T>::get_root()
{
    return this->root; // Get the root of the BST
}

template <typename T> // Duplicates are not allowed
node<T> *BST<T>::insert(node<T> *root_ptr, const T &data)
{
    if (root_ptr == NULL)
    {
        return get_new_node(data);
    }
    else if (data < root_ptr->data)
    {
        root_ptr->left = insert(root_ptr->left, data);
    }
    else if (data > root_ptr->data)
    {
        root_ptr->right = insert(root_ptr->right, data);
    }
    return root_ptr;
}

template <typename T>
void BST<T>::add(const T &data)
{
    this->len++;
    this->root = insert(this->root, data);
}

template <typename T>
node<T> *BST<T>::search(node<T> *root_ptr, const T &data)
{
    if (root_ptr == NULL)
    {
        return NULL;
    }
    else if (root_ptr->data == data)
    {
        return root_ptr;
    }
    else if (root_ptr->data < data)
    {
        search(root_ptr->right, data);
    }
    else
    {
        search(root_ptr->left, data);
    }
}

template <typename T>
node<T> *BST<T>::find(const T &data)
{
    return search(this->root, data);
}

template <typename T>
void BST<T>::print_preorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    cout << root_ptr->data << ' ';
    print_preorder(root_ptr->left);
    print_preorder(root_ptr->right);
}

template <typename T>
void BST<T>::print_inorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    print_inorder(root_ptr->left);
    cout << root_ptr->data << ' ';
    print_inorder(root_ptr->right);
}

template <typename T>
void BST<T>::print_postorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    print_postorder(root_ptr->left);
    print_postorder(root_ptr->right);
    cout << root_ptr->data << ' ';
}

template <typename T>
node<T> *BST<T>::find_min(node<T> *root_ptr)
{
    while (root_ptr->left != NULL)
    {
        root_ptr = root_ptr->left;
    }
    return root_ptr;
}

template <typename T>
node<T> *BST<T>::find_max(node<T> *root_ptr)
{
    while (root_ptr->right != NULL)
    {
        root_ptr = root_ptr->right;
    }
    return root_ptr;
}

template <typename T>
void BST<T>::remove_all(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    remove_all(root_ptr->left);
    remove_all(root_ptr->right);
    delete root_ptr;
}

template <typename T>
node<T> *BST<T>::inorder_successor(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return NULL;
    }
    // Now if the node has a right subtree return the minimum of that subtree
    if (root_ptr->right != NULL)
    {
        return find_min(root_ptr->right);
    }
    else
    {
        // Traverse the tree from the root node until that value is found (value=>node of which successor is to be found)
        node<T> *successor = NULL;
        node<T> *ancestor = this->root;
        while (ancestor != root_ptr)
        {
            if (root_ptr->data < ancestor->data)
            {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else
            {
                ancestor = ancestor->right;
            }
        }
        return successor;
    }
}

int main()
{
    BST<int> tree;
    int ch;
    while (cin >> ch)
    {
        if (ch == -1)
            break;
        tree.add(ch);
    }
    tree.print_inorder(tree.get_root());
    cout << '\n';
    node<int> *node_ref = tree.find_min(tree.get_root());
    cout << node_ref->data << '\n';
    node_ref = tree.find_max(tree.get_root());
    cout << node_ref->data << '\n';
    cout << tree.find(120)->data << ' ';
    cout << tree.inorder_successor (tree.find (120))->data << ' ';
    cout << tree.inorder_successor (tree.find (23))->data << ' ';
    cout << tree.inorder_successor (tree.find (15))->data << ' ';
    cout << tree.inorder_successor (tree.find (32))->data << ' ';
    cout << tree.inorder_successor (tree.find (26))->data << ' ';
    cout << tree.inorder_successor (tree.find (12))->data << ' ';
    cout << tree.inorder_successor (tree.find (14))->data << ' ';
    // cout << tree.inorder_successor (tree.find (123))->data << ' ';
    cout << tree.inorder_successor (tree.find (56))->data << ' ';
    return 0;
}
