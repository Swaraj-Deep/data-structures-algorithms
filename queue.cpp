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
class queue
{ // Queue implementation *zero based indexing*
private:
    int len;                           // Holds the length of the queue
    node<T> *head;                     // Holds the pointer to the head of the queue
    node<T> *tail;                     // Holds the pointer to the tail of the queue
    node<T> *get_new_node(const T &);  // Function to get the new node for the queue
    void insert_first_node(const T &); // Function to insert node at first position
    void remove_all();                 // Remove all the nodes from the queue
public:
    queue();                   // Constructor of the queue
    ~queue() { remove_all(); } // Destructor of the queue
    void append(const T &);    // Append a given element to the tail of the queue
    bool remove();             // Remove the node from the front of the queue
    T peek();                  // Return the first element of the queue
    int length();              // Return the number of elements present in the queue
    bool find(const T &);      // Return true if the element is found
    node<T> *get_head_node();  // Return the pointer to the head node of the queue
    bool is_empty();           // Return true if queue is empty
};

template <typename T>
queue<T>::queue()
{
    this->len = 0;     // Set the length of the queue to zero
    this->head = NULL; // Set the head pointer to NULL
    this->tail = NULL; // Set the tail to NULL
}

template <typename T> // Create the new node
node<T> *queue<T>::get_new_node(const T &data)
{
    node<T> *new_node = new node<T>;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

template <typename T> // Append to the end of the stack
void queue<T>::append(const T &data)
{
    this->len++;
    if (this->head == NULL && this->tail == NULL) // Check whether the queue is empty or not
    {
        node<T> *new_node = get_new_node(data);
        head = new_node;
        tail = new_node;
        return;
    }
    node<T> *new_node = get_new_node(data);
    this->tail->next = new_node; // Adjusting the links
    this->tail = new_node;
    return;
}

template <typename T> // Get the pointer to the head node of the stack
node<T> *queue<T>::get_head_node()
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

template <typename T> // Get the node at front in the queue
T queue<T>::peek()
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

template <typename T> // Get the length of the queue
int queue<T>::length()
{
    return this->len;
}

template <typename T> // Check whether the node exist or not
bool queue<T>::find(const T &key)
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
bool queue<T>::remove()
{
    try
    {
        if (this->len <= 0)
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
void queue<T>::remove_all()
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
bool queue<T>::is_empty()
{
    return this->len > 0 ? false : true;
}
