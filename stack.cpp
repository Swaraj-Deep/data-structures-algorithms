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
{               // Node structure of the list
    T data;     // Hold the data part of the node
    node *next; // Hold the pointer to the next node
};

template <typename T>
class stack
{ // Stack implementation *zero based indexing*
private:
    int len;                           // Holds the length of the stack
    node<T> *head;                     // Holds the pointer to the head of the stack
    node<T> *get_new_node(const T &);  // Function to get the new node for the stack
    void insert_first_node(const T &); // Function to insert node at first position
    void remove_all();                 // Remove all the nodes from the stack
public:
    stack();                   // Constructor of the stack
    ~stack() { remove_all(); } // Destructor of the stack
    void append(const T &);    // Append a given element to the last
    bool remove();             // Remove the last node of the stack
    T peek();                  // Return the last element of the stack
    int length();              // Return the number of elements present in the stack
    bool find(const T &);      // Return true if the element is found
    node<T> *get_head_node();  // Return the head node of the stack
    bool is_empty();           // Return true if stack is empty
};

template <typename T>
stack<T>::stack()
{
    this->len = 0;     // Set the length of the stack to zero
    this->head = NULL; // Set the head pointer to NULL
}

template <typename T> // Create the new node
node<T> *stack<T>::get_new_node(const T &data)
{
    node<T> *new_node = new node<T>;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

template <typename T> // Append to the end of the stack
void stack<T>::append(const T &data)
{
    this->len++;
    if (!head) // Check whether the head is NULL or not
    {
        node<T> *new_node = get_new_node(data);
        head = new_node;
        return;
    }
    node<T> *new_node = get_new_node(data);
    new_node->next = head; // Adjusting the links
    head = new_node;
    return;
}

template <typename T> // Get the head node of the list
node<T> *stack<T>::get_head_node()
{
    try
    {
        // Verify the length
        if (this->len > 0)
            return this->head;
        throw runtime_error("Exception: Illegal operation called");
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T> // Get the first node of the Linked list
T stack<T>::peek()
{
    try
    {
        // Verify the length
        if (this->len > 0)
        {
            return this->head->data;
        }
        throw runtime_error("Exception: Illegal operation called");
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T> // Get the length of the linked list
int stack<T>::length()
{
    return this->len;
}

template <typename T> // Check whether the node exist or not
bool stack<T>::find(const T &key)
{
    node<T> *head = get_head_node();
    while (head)
    {
        if (head->data == key)
        {
            return true; // Return true if node found
        }
        head = head->next;
    }
    return false;
}

template <typename T> // Remove last node
bool stack<T>::remove()
{
    try
    {
        if (this->len <= 0 || this->head == NULL)
        {
            throw runtime_error("Exception: Illegal operation called");
        }
        node<T> *temp = head;
        head = head->next;
        delete temp;
        this->len--;
        return true;
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
    return false;
}

template <typename T> // Remove all the nodes of the stack
void stack<T>::remove_all()
{
    node<T> *temp = NULL;
    while (head)
    {
        temp = head;
        delete temp;
        head = head->next;
        this->len--;
    }
}

template <typename T>
bool stack<T>::is_empty()
{
    return this->len > 0 ? false : true;
}
