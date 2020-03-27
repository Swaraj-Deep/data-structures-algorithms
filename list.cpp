/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

template <typename T>
class list
{
private:
  void operator=(const list &) {} // Protect the assignment operator
  list(const list &) {}           // Protect the copy constructor
public:
  list() {}                                // Default Constructor
  ~list() {}                               // Default Destructor
  virtual void insert(const T &, int) = 0; // Insert a given element to the postion
  virtual void append(const T &) = 0;      // Append a given element to the last
  virtual T peek_first() = 0;              // Return the last element in the list
  virtual bool remove_at(int) = 0;         // Return true if the element is removed from the index
  virtual bool remove(const T &) = 0;      // Return true if the element is removed
  virtual int length() = 0;                // Return the number of elements present in the list
  virtual bool find(const T &) = 0;        // Return true if the element is found
};