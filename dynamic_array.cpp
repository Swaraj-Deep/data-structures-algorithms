/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <algorithm>
#include <exception>

using namespace std;

template<typename T>
class dynamic_array { // Class template for dynamic array
private:
  int len;  // To store the length of the array
  int capacity; // To store the actual capacity of the array
  T* arr; // Actual array
  void operator = (const dynamic_array&) {} // Protect the assignment operator
  dynamic_array(const dynamic_array&) {} // Protect copy constructor
public:
  int size ();  // Get the size of the array
  bool is_empty (); // Check whether the array is empty of not
  T get_elem_at (int p_index);  // Get the element at index p_index
  void append (T obj);  // Append the obj to the last of the array
  int index_of (T obj); // Get the index of the given obj
  T remove_at (int p_index);  // Remove the element from the index p_index
  T remove (T obj); // Remove the obj from the array
  T operator[] (int p_index); // Overloading subscript operator for just getting the value at p_index
  dynamic_array (int p_capacity)  // Constructor with the given capacity
    : len{0}
    , capacity{p_capacity}
  {
    if (p_capacity < 0) {
      cerr << "Exception: Capacity cannot be negative.\n";
      capacity = 4;
    }
    if (capacity == 0) capacity = 4;
    arr = new T[capacity]; // Should be a try catch block here but too lazy to implement it
  }
  dynamic_array () {  // Non parametrized Constructor
    len = 0;
    capacity = 4;
    arr = new T[capacity];
  }
  ~dynamic_array () { // Destructor 
      delete[] arr;
  }
  T* get_start_ptr () { // Get the pointer to the start of the array;
    return arr;
  }
  void clear () {
    len = 0;
    capacity = 0;
    delete [] arr;
  }
};

template <typename T>
int dynamic_array<T>::size () {
  return this->len;
}

template <typename T>
bool dynamic_array<T>::is_empty () {
  return size () == 0;
}

template <typename T>
T dynamic_array<T>::get_elem_at (int p_index) {
  try {
    // Check if the index is valid or not
    if (p_index < 0 || p_index >= capacity) {
      throw runtime_error ("Exception: array_index_out_of_bounds.");
    }
    // Return the object at the given index
    return arr[p_index];
  } catch (const exception& e) {
    // If exception occurs
    cerr << e.what () << '\n';
  }
}

template <typename T>
void dynamic_array<T>::append (T obj) {
  // Checks if there is a need to resize the array
  if (len + 1 > capacity) {
    capacity *= 2;
    T* new_arr = new T[capacity];
    for (int i = 0; i < len; ++i) {
      new_arr[i] = arr[i]; // Copies the content to a temporary array;
    }
    arr = new_arr;
  }
  arr[len++] = obj;
}

template <typename T>
int dynamic_array<T>::index_of (T obj) {
  int pos = -1;
  for (int i = 0; i < len; ++i) {
    if (arr[i] == obj) {
      pos = i;
      break;
    }
  }
  try {
    // Checks if the obj is present in the array or not
    if (pos == -1) {
      throw runtime_error ("Exception: Element not found.");
    }
    return pos;
  } catch (const exception& e) {
    cerr << e.what () << '\n';
  }
}

template <typename T>
T dynamic_array<T>::remove_at (int p_index) {
  try {
    // Check if the index is valid or not
    if (p_index < 0 || p_index >= len) {
      throw runtime_error ("Exception: array_index_out_or_bounds.");
    }
    T del_data = arr[p_index];
    T* new_arr = new T[len - 1];
    // Copies the elements except at p_index
    for (int i = 0, j = 0; i < len; ++i, ++j) {
      if (i == p_index) {
        j--;
      } else {
        new_arr[j] = arr[i];
      }
    }
    arr = new_arr;
    capacity = --len;
    return del_data;
  } catch (const exception& e) {
    cerr << e.what () << '\n';
  }
}

template <typename T>
T dynamic_array<T>::remove (T obj) {
  try {
    int pos = -1;
    for (int i = 0; i < len; ++i) {
      if (arr[i] == obj) {
        pos = i;
        break;
      }
    }
    // Checks if the given elem is present or not
    if (pos == -1) {
      throw runtime_error ("Exception: Element not found.");
    }
    remove_at (pos);
  } catch (const exception& e) {
    cerr << e.what () << '\n';
  }
}

template <typename T>
T dynamic_array<T>::operator[] (int p_index) {
  try {
    // Check for whether p_index is valid or not
    if (p_index < 0 || p_index >= len) {
      throw runtime_error ("Exception: array_index_out_of_bounds.");
    }
    // Return the element at p_index
    return arr[p_index];
  } catch (const exception& e) {
    cerr << e.what () << '\n';
  }
}

// Driver Program
int main () {
  ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
  dynamic_array<int> a(5), b;
  a.append (1002);
  a.append (-9);
  for (int i = 0; i < 5; ++i) {
    a.append (i + 10);
  }
  a.append (0);
  a.append (8);
  a.append (-10);
  // b = a; Will give error as assignment operator is private with this context
  cout << "Array b: ";
  for_each (b.get_start_ptr(), b.get_start_ptr () + b.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  cout << "Before Sorting: ";
  for_each (a.get_start_ptr(), a.get_start_ptr () + a.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  cout << "After Sorting: ";
  sort (a.get_start_ptr (), a.get_start_ptr () + a.size ());
  for_each (a.get_start_ptr(), a.get_start_ptr () + a.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  cout << "After removing 1002: ";
  a.remove (1002);
  for_each (a.get_start_ptr(), a.get_start_ptr () + a.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  cout << "After removing 10: ";
  a.remove (10);
  for_each (a.get_start_ptr(), a.get_start_ptr () + a.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  cout << "After removing -10: ";
  a.remove (-10);
  for_each (a.get_start_ptr(), a.get_start_ptr () + a.size (), [](int x){cout << x << ' ';});
  cout << '\n';
  return 0;
}