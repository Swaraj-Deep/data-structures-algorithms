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
{             // Node structure of the list
  T data;     // Hold the data part of the node
  node *next; // Hold the pointer to the next node
};

template <typename T>
class singly_linked_list : public list<T>
{ // Linked list implementation *zero based indexing*
private:
  int len;                           // Holds the length of the list
  node<T> *head;                     // Holds the pointer to the head of the list
  node<T> *get_new_node(const T &);  // Function to get the new node for the list
  void insert_first_node(const T &); // Function to insert node at first position
  void remove_all();                 // Remove all the nodes from the list
public:
  singly_linked_list();                   // Constructor of the linked list
  ~singly_linked_list() { remove_all(); } // Destructor of the linked list
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
singly_linked_list<T>::singly_linked_list()
{
  this->len = 0;     // Set the length of the list to zero
  this->head = NULL; // Set the head pointer to NULL
}

template <typename T> // Create the new node
node<T> *singly_linked_list<T>::get_new_node(const T &data)
{
  node<T> *new_node = new node<T>;
  new_node->data = data;
  new_node->next = NULL;
  return new_node;
}

template <typename T> // Append to the end of the linked_list
void singly_linked_list<T>::append(const T &data)
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
node<T> *singly_linked_list<T>::get_head_node()
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
T singly_linked_list<T>::peek_first()
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
int singly_linked_list<T>::length()
{
  return this->len;
}

template <typename T> // Check whether the node exist or not
bool singly_linked_list<T>::find(const T &key)
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

template <typename T> // Insert to the begining
void singly_linked_list<T>::insert_first_node(const T &data)
{
  node<T> *new_node = get_new_node(data);
  new_node->next = head;
  head = new_node;
  return;
}

template <typename T> // Inser at a given position
void singly_linked_list<T>::insert(const T &data, int index)
{
  try
  {
    // Verify the index
    if (index < 0 || index > len)
    {
      throw runtime_error("Exception: index out of bounds");
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
        new_node->next = head->next;
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

template <typename T> // Remove a node
bool singly_linked_list<T>::remove(const T &key)
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
      delete temp;
      this->len--;
      return true;
    }
    node<T> *head_node_ref = get_head_node();
    node<T> *prev = NULL;
    while (head_node_ref)
    {
      if (head_node_ref->data == key)
      {
        prev->next = head_node_ref->next;
        delete head_node_ref;
        this->len--;
        return true;
      }
      prev = head_node_ref;
      head_node_ref = head_node_ref->next;
    }
  }
  catch (const exception &e)
  {
    cout << e.what() << '\n';
  }
  return false;
}

template <typename T> // Remove the node at given index
bool singly_linked_list<T>::remove_at(int index)
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
      delete temp;
      this->len--;
      return true;
    }
    node<T> *head_node_ref = get_head_node();
    node<T> *prev = NULL;
    int current_index{0};
    while (head_node_ref)
    {
      if (current_index == index)
      {
        prev->next = head_node_ref->next;
        delete head_node_ref;
        this->len--;
        return true;
      }
      current_index++;
      prev = head_node_ref;
      head_node_ref = head_node_ref->next;
    }
  }
  catch (const exception &e)
  {
    cout << e.what() << '\n';
  }
}

template <typename T> // Remove all the nodes of the linked list
void singly_linked_list<T>::remove_all()
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
