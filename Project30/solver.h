#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "stack.h"

class solver_t {
public:
    solver_t();     // Solver constructor
    ~solver_t();    // Solver destructor

    // Parse the equation into separate terms.
    void parse(std::string m_equation);
    // Convert the infix equation to postfix expression.
    void convert_to_postfix();
    // Calculate the postfix equation.
    void calculate();
    // Reset the solver.
    void reset();
    // Print the contents of stack.
    void print() const;

private:
    // Check if the string is a number.
    bool is_number(std::string m_string) const;
    // Check if the string is a positive number.
    bool is_pos_number(std::string m_string) const;
    // Check if the string is a negative number.
    bool is_neg_number(std::string m_string) const;
    // Check if the string is an operator.
    bool is_operator(std::string m_string) const;
    // Check if the character is an operator.
    bool is_operator(char m_char) const;
    // Check if the string is a paren.
    bool is_paren(std::string m_string) const;
    // Check if the character is a paren.
    bool is_paren(char m_char) const;

    Stack_t stack;          // Solver stack
    std::string numbers;    // Number characters
    std::string operators;  // Operator characters
    std::string parens;     // Parens characters
};

#endif

