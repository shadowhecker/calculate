#ifndef __STACK_H__
#define __STACK_H__

#include <string>

typedef std::string element_t;

class Stack_t {
public:
    Stack_t();          // Stack constructor
    ~Stack_t();         // Stack destructor

    // Get the number of elements in the stack.
    size_t size() const;
    // Print all elements in the stack.
    void print() const;
    // Add an element at the end of stack.
    void push(const element_t m_element);
    // Remove the last element in the stack.
    element_t pop();
    // Remove all elements in the stack.
    void clear();
    // Returns the reference of top element.
    element_t& top();
private:
    // Increase the array size.
    void resize(const size_t m_array_size);

    element_t *array;   // Array of elements
    size_t array_size;  // Array size should be at least num_elements.
    size_t num_elements;// Number of elements cannot exceed array_size.
};

#endif

