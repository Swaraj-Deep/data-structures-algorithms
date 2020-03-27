/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <exception>
#include "list.cpp"

using namespace std;

template <typename T>
struct node
{               // Node structure of the list
    T data;     // Hold the data part of the node
    node *next; // Hold the pointer to the next node
    node *prev; // Hold the pointer to the previous node
};

template <typename T>
class doubly_linked_list
{ // Doubly Linked List implementation *Zero Based Indexing*
private:
    int len;                           // Hold the current length of the doubly linked list
    node<T> *head;                     // Hold the head pointer to the doubly linked list
    node<T> *get_new_node(const T &);  // Function to get the new node for the Doubly linked list
    void insert_first_node(const T &); // Function to insert node at first position
    void remove_all();                 // Remove all the nodes from the list
public:
    doubly_linked_list();                   // Constructor of the linked list
    ~doubly_linked_list() { remove_all(); } // Destructor of the linked list
    void insert(const T &, int);            // Insert a given element to the postion
    void append(const T &);                 // Append a given element to the last
    T peek_first();                         // Return the first element in the list
    bool remove_at(int);                    // Return true if the element is removed from the index
    bool remove(const T &);                 // Return true if the element is removed
    int length();                           // Return the number of elements present in the list
    bool find(const T &);                   // Return true if the element is found
    node<T> *get_head_node();               // Return the head node of the list;
};

template <typename T>
int doubly_linked_list<T>::length()
{
    return this->len; // Get the length of the list
}

template <typename T>
doubly_linked_list<T>::doubly_linked_list()
{
    this->len = 0;     // Set the length of the doubly linked list to zero
    this->head = NULL; // Set the head node to NULL
}

template <typename T> // Utility funciton for creating a new node
node<T> *doubly_linked_list<T>::get_new_node(const T &data)
{
    node<T> *new_node = new node<T>;
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

template <typename T> // Append the node to the list
void doubly_linked_list<T>::append(const T &data)
{
    this->len++;
    if (!this->head)
    { // If the head is NULL
        node<T> *new_node = get_new_node(data);
        head = new_node;
        return;
    }
    node<T> *new_node = get_new_node(data);
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
}

template <typename T> // Return the pointer to the first node of the list
node<T> *doubly_linked_list<T>::get_head_node()
{
    try
    {
        // Verify the list
        if (this->len <= 0)
        {
            throw runtime_error("Exception: Invalid Operation called");
        }
        return this->head;
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T>
T doubly_linked_list<T>::peek_first()
{
    try
    {
        if (this->len <= 0)
        {
            throw runtime_error("Exception: Illegal Operation Called");
        }
        return this->head->data;
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T>
bool doubly_linked_list<T>::find(const T &key)
{
    try
    {
        if (this->len <= 0)
        {
            throw runtime_error("Exception: Illegal operation called.");
        }
        node<T> *head = get_head_node();
        while (head)
        {
            if (head->data == key)
            {
                return true;
            }
            head = head->next;
        }
        return false;
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T>
void doubly_linked_list<T>::insert_first_node(const T &data)
{
    node<T> *new_node = new node<T>;
    new_node = get_new_node(data);
    new_node->next = head;
    head->prev = new_node;
    head = new_node;
}

template <typename T>
void doubly_linked_list<T>::insert(const T &data, int index)
{
    try
    {
        if (index < 0 || index > this->len)
        {
            throw runtime_error("Exception: Index out of bounds");
        }
        this->len++;
        if (index == 0)
        {
            insert_first_node(data);
        }
        node<T> *head = get_head_node();
        int current_index{1};
        node<T> *new_node = NULL;
        while (head)
        {
            if (current_index == index)
            {
                new_node = get_new_node(data);
                if (head->next == NULL)
                { // If this is the last node of the list
                    new_node->prev = head;
                    head->next = new_node;
                    return;
                }
                new_node->next = head->next;
                head->next->prev = new_node;
                new_node->prev = head;
                head->next = new_node;
                break;
            }
            current_index++;
            head = head->next;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T>
bool doubly_linked_list<T>::remove(const T &key)
{
    try
    {
        if (this->len <= 0 || this->head == NULL)
        {
            throw runtime_error("Exception: Illegal operation called");
        }
        if (len == 1)
        {
            node<T> *temp = this->head;
            this->head = NULL;
            delete temp;
            this->len--;
            return true; // If removed return true else return false
        }
        if (this->head->data == key)
        {
            node<T> *temp = this->head;
            this->head = this->head->next;
            head->prev = NULL;
            delete temp;
            this->len--;
            return true;
        }
        node<T> *head_node_ref = get_head_node();
        while (head_node_ref)
        {
            if (head_node_ref->data == key)
            {
                if (head_node_ref->next == NULL)
                { // If this is the last Node of the list
                    head_node_ref->prev->next = NULL;
                    delete head_node_ref;
                    this->len--;
                    return true;
                }
                head_node_ref->prev->next = head_node_ref->next;
                head_node_ref->next->prev = head_node_ref->prev;
                delete head_node_ref;
                this->len--;
                return true;
            }
            head_node_ref = head_node_ref->next;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
    return false;
}

template <typename T>
bool doubly_linked_list<T>::remove_at(int index)
{
    try
    {
        // Verify the given index
        if (this->len <= 0 || index < 0 || index >= this->len)
        {
            throw runtime_error("Exception: Illegal operation called");
        }
        if (len == 1)
        {
            node<T> *temp = this->head;
            this->head = NULL;
            delete temp;
            this->len--;
            return true;
        }
        if (index == 0)
        {
            node<T> *temp = this->head;
            this->head = this->head->next;
            this->head->prev = NULL;
            delete temp;
            this->len--;
            return true;
        }
        node<T> *head_node_ref = get_head_node();
        int current_index{0};
        while (head_node_ref)
        {
            if (current_index == index)
            {

                if (head_node_ref->next == NULL)
                { // If this is the last Node of the list
                    head_node_ref->prev->next = NULL;
                    delete head_node_ref;
                    this->len--;
                    return true;
                }
                head_node_ref->prev->next = head_node_ref->next;
                head_node_ref->next->prev = head_node_ref->prev;
                delete head_node_ref;
                this->len--;
                return true;
            }
            current_index++;
            head_node_ref = head_node_ref->next;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}

template <typename T>
void doubly_linked_list<T>::remove_all()
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
