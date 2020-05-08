/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <queue>

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
    int len;                                    // Keeps track of current number of elements in the BST
    node<T> *root;                              // stores the root node of the BST
    node<T> *get_new_node(const T &);           // get the new node for the BST
    void remove_all(node<T> *);                 // Remove all the nodes from the BST
    node<T> *insert(node<T> *, const T &);      // helper to insert the node to the BST
    node<T> *search(node<T> *, const T &);      // helper to search for the data in BST
    node<T> *delete_node(node<T> *, const T &); // helper to delete the node of the BST
public:
    BST();                                 // Constructor of the BST
    ~BST();                                // Destructor of the BST
    int get_length();                      // Get the length of the BST
    void add(const T &);                   // Add the given element to the BST
    node<T> *find(const T &);              // Check whether the given element is present in the BST or not
    node<T> *get_root();                   // get the root of the BST
    void remove(const T &);                // Remove a given node from the BST and return the reference of the root node
    void print_preorder(node<T> *);        // Prints the preorder of the BST
    void print_inorder(node<T> *);         // Prints the inorder of the BST
    void print_postorder(node<T> *);       // Prints the postorder of the BST
    void print_levelorder(node<T> *);      // Prints the levelorder of the BST
    node<T> *inorder_successor(node<T> *); // Returns the reference to the inorder successor of the given node roference
    node<T> *find_min(node<T> *);          // Returns the reference to the minimum element in the passed reference
    node<T> *find_max(node<T> *);          // Returns the reference to the maxm element in the passed reference
    int get_height(node<T> *);             // Returns the height of the tree
};

template <typename T>
int BST<T>::get_height(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return -1;
    }
    return (max(get_height(root_ptr->left), get_height(root_ptr->right)) + 1);
}

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
    this->len = 0;
    remove_all(this->root);
    this->root = NULL;
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
    else
    {
        cout << root_ptr->data << ' ';
        print_preorder(root_ptr->left);
        print_preorder(root_ptr->right);
    }
}

template <typename T>
void BST<T>::print_inorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    else
    {
        print_inorder(root_ptr->left);
        cout << root_ptr->data << ' ';
        print_inorder(root_ptr->right);
    }
}

template <typename T>
void BST<T>::print_levelorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    else
    {
        queue<node<T> *> node_queue;
        node_queue.push(root_ptr);
        while (!node_queue.empty())
        {
            node<T> *current_node = node_queue.front();
            cout << current_node->data << ' ';
            node_queue.pop();
            if (current_node->left)
            {
                node_queue.push(current_node->left);
            }
            if (current_node->right)
            {
                node_queue.push(current_node->right);
            }
        }
    }
}

template <typename T>
void BST<T>::print_postorder(node<T> *root_ptr)
{
    if (root_ptr == NULL)
    {
        return;
    }
    else
    {
        print_postorder(root_ptr->left);
        print_postorder(root_ptr->right);
        cout << root_ptr->data << ' ';
    }
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

template <typename T>
node<T> *BST<T>::delete_node(node<T> *root_ptr, const T &data)
{
    if (root_ptr == NULL)
    {
        return root_ptr;
    }
    else if (data < root_ptr->data)
    {
        root_ptr->left = delete_node(root_ptr->left, data);
    }
    else if (data > root_ptr->data)
    {
        root_ptr->right = delete_node(root_ptr->right, data);
    }
    else
    {
        // Node to be deleted has been found here
        // Case 1: No Child
        if (root_ptr->left == NULL && root_ptr->right == NULL)
        {
            delete root_ptr;
        }
        else if (root_ptr->left == NULL)
        { // Case 2: One Child
            node<T> *temp = root_ptr;
            root_ptr = root_ptr->right;
            delete temp;
        }
        else if (root_ptr->right == NULL)
        {
            node<T> *temp = root_ptr;
            root_ptr = root_ptr->left;
            delete temp;
        }
        else
        {
            // Case 3: With both the children
            node<T> *temp = find_min(root_ptr->right); // We could also find the maximum of the left subtree
            root_ptr->data = temp->data;
            root_ptr->right = delete_node(root_ptr->right, temp->data);
        }
    }
    return root_ptr;
}

template <typename T>
void BST<T>::remove(const T &data)
{
    this->root = delete_node(this->root, data);
    this->len--;
    return;
}
