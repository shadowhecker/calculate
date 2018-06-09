#include <assert.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include "stack.h"

using namespace std;

// Stack constructor
Stack_t::Stack_t() :
    array(NULL),
    array_size(64),
    num_elements(0) {
    array = (element_t*)malloc(sizeof(element_t)*array_size);
}

// Stack destructor
Stack_t::~Stack_t() {
    clear(); free(array);
}

// Get the number of elements in the stack.
size_t Stack_t::size() const {
    return num_elements;
}

// Print all elements in the stack.
void Stack_t::print() const {
    for(size_t i = 0; i < num_elements; i++) { cout << array[i] << " "; }
    cout << "[top_of_stack]" << endl;
}

// Add an element at the end of stack.
void Stack_t::push(const element_t m_element) {
    if(num_elements == array_size) resize(2*array_size);
    new(&array[num_elements++])element_t(m_element);
}

// Remove the last element in the list.
element_t Stack_t::pop() {
    assert(num_elements);
    element_t top_element(array[num_elements-1]);
    array[--num_elements].~element_t();
    return top_element;
}

// Returns the value of top element (not guaranteed).
element_t& Stack_t::top() {
    assert(num_elements);
    return array[num_elements-1];
}

// Remove all elements in the list.
void Stack_t::clear() {
    for(size_t i = 0; i < num_elements; i++) { array[i].~element_t(); }
    num_elements = 0;
}

// Increase the array size.
void Stack_t::resize(const size_t m_array_size) {
    assert(m_array_size > array_size);
    array_size = m_array_size;
    element_t *old_array = array;
    array = (element_t*)malloc(sizeof(element_t)*array_size);
    for(size_t i = 0; i < num_elements; i++) {
        new (&array[i])element_t(old_array[i]);
        old_array[i].~element_t();
    }
    free(old_array);
}

