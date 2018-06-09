#include <cstdlib>
#include <iostream>
#include <sstream>
#include "solver.h"

using namespace std;



/***************************
 * EEE2020-03 ASSIGNMENT 3 *
 ***************************/
// Convert the infix equation to postfix expression.
void solver_t::convert_to_postfix() {
	Stack_t operator_stack,equation_stack;//操作数栈,操作符栈,最后形成的栈
	element_t term;
	while (stack.size()!=0)
	{
		term = stack.pop();
		if (term == "(")
		{
			operator_stack.push(term);
		}
		else if (term == ")")
		{
			while (operator_stack.top() != "(")
			{
				equation_stack.push(operator_stack.pop());
			}
			operator_stack.pop();
		}
		else if (term == "+" || term == "-")
		{
			while (operator_stack.size() != 0 && operator_stack.top() != "(")
			{
				equation_stack.push(operator_stack.pop());
			}
			operator_stack.push(term);
		}
		else if (term == "*" || term == "/")
		{
			while (operator_stack.size() != 0 && operator_stack.top() != "(" && (operator_stack.top() == "*" || operator_stack.top() == "/"))
			{
				equation_stack.push(operator_stack.pop());
			}
			operator_stack.push(term);
		}
		else
		{
			while (is_number(term))
			{
				equation_stack.push(term);
				if (stack.size() == 0)
					break;
				term = stack.pop();
			}
			if(!is_number(term))
				stack.push(term);
		}
	}
	while (operator_stack.size() != 0)
	{
		equation_stack.push(operator_stack.pop());
	}
	while (equation_stack.size() != 0)
	{
		stack.push(equation_stack.pop());
	}
}

// Calculate the postfix equation.
void solver_t::calculate() {
	Stack_t number_stack;
	element_t term;
	while (stack.size() != 0)
	{
		term = stack.pop();
		if (term == "+")
		{
			double operand2 = atof(number_stack.pop().c_str());
			double operand1 = atof(number_stack.pop().c_str());
			double result = operand1 + operand2;
			stringstream ss;
			ss << result;
			number_stack.push(ss.str());
		}
		else if (term == "-")
		{
			double operand2 = atof(number_stack.pop().c_str());
			double operand1 = atof(number_stack.pop().c_str());
			double result = operand1 - operand2;
			stringstream ss;
			ss << result;
			number_stack.push(ss.str());
		}
		else if (term == "*")
		{
			double operand2 = atof(number_stack.pop().c_str());
			double operand1 = atof(number_stack.pop().c_str());
			double result = operand1 * operand2;
			stringstream ss;
			ss << result;
			number_stack.push(ss.str());
		}
		else if (term == "/")
		{
			if (atof(number_stack.top().c_str()) != 0)
			{
				double operand2 = atof(number_stack.pop().c_str());
				double operand1 = atof(number_stack.pop().c_str());
				double result = operand1 / operand2;
				stringstream ss;
				ss << result;
				number_stack.push(ss.str());
			}
			else
			{
				cout << "除数是0" << endl;
				system("pause");
				exit(0);
			}
		}
		else
		{
			number_stack.push(term);
		}
	}
	stack.push(number_stack.pop());
}
/***********************
 * END OF ASSIGNMENT 3 *
 ***********************/



// Solver constructor
solver_t::solver_t() :
    numbers(".0123456789"), // Number characters including point "."
    operators("+-*/"),      // Operator characters
    parens("()")            // Parens characters
{}

// Solver destructor
solver_t::~solver_t() {}

// Check if the string is a number.
bool solver_t::is_number(string m_string) const {
    return is_pos_number(m_string) || is_neg_number(m_string);
}

// Check if the string is a positive number.
bool solver_t::is_pos_number(string m_string) const {
    return m_string.find_first_not_of(numbers) == string::npos;
}

// Check if the string is a negative number.
bool solver_t::is_neg_number(string m_string) const {
    return (m_string.size() > 1) && (m_string[0] == '-') &&
           (m_string.find_first_not_of(numbers, 1) == string::npos);
}

// Check if the string is an operator.
bool solver_t::is_operator(string m_string) const {
    return (m_string.size() == 1) &&
           (operators.find(m_string) != string::npos);
}

// Check if the character is an operator.
bool solver_t::is_operator(char m_char) const {
    return operators.find(m_char) != string::npos;
}

// Check if the string is a paren.
bool solver_t::is_paren(string m_string) const {
    return (m_string.size() == 1) &&
           (parens.find(m_string) != string::npos);
}

// Check if the character is a paren.
bool solver_t::is_paren(char m_char) const {
    return parens.find(m_char) != string::npos;
}

// Parse the equation into separate terms.
void solver_t::parse(string m_equation) {
    // Check if the given equation has illegal characters.
    size_t err = m_equation.find_first_not_of(numbers+operators+parens+" ");
    if(err != string::npos) {
        cerr << "Error: equation has non-numeric characters or unknown operators " << m_equation[err] << endl;
        cerr << "Equation: " << m_equation << endl;
        exit(1);
    }

    Stack_t temp; // Temporary stack to store parsed terms in reverse order
    for(size_t i = 0; i < m_equation.size(); ) {
        if(m_equation[i] == ' ') { i++; } // Skip spaces.
        else {
            // Check if the character is an operator or paren.
            if(is_operator(m_equation[i]) || is_paren(m_equation[i])) {
                temp.push(string(1, m_equation[i++]));
            }
            else {
                // Otherwise, it must be a number. A number may have multiple characters.
                size_t end    = m_equation.find_first_not_of(numbers, i);
                size_t length = (end == string::npos ? m_equation.size() : end) - i;
                string number = m_equation.substr(i, length);
                i += length;
                temp.push(number);
            }
        }
    }

    int brackets = 0; // Check if parens have correct pairs.
    while(temp.size()) {
        // Collect equation terms one by one, from the temporary stack.
        string term = temp.pop();

        // Check if every equation term is sane.
        if(is_operator(term)) {
            // Equation ends with an operator.
            if(!stack.size()) {
                cerr << "Error: equation ends with an illegal expression " << term << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
            // Operator is followed by another operator or ).
            if(is_operator(stack.top()) || (stack.top() == ")")) {
                cerr << "Error: equation has an illegal expression " << term << " " << stack.top() << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
            // Merge minus sign with the following number.
            if((term == "-") && is_pos_number(stack.top()) && (!temp.size() ||
                is_operator(temp.top()) || (temp.top() == "("))) { term = "-"+stack.pop(); }
        }
        else if(is_number(term)) {
            // Number is followed by another number or (.
            if(stack.size()) {
                if(is_number(stack.top()) || (stack.top() == "(")) {
                    cerr << "Error: equation has an illegal expression " << term << " " << stack.top() << endl;
                    cerr << "Equation: " << m_equation << endl;
                    exit(1);
                }
            }
            // Check if floating-point number format is correct.
            size_t point = term.find(".");
            if((point != string::npos) && ((term.find(".",point+1) != string::npos) ||
               (point == term.size()-1) || !point)) {
                cerr << "Error: illegal floating-point number format " << term << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
        }
        else if(term == "(") {
            // Equation ends with (.
            if(!stack.size()) {
                cerr << "Error: equation ends with an illegal expression " << term << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
            // ( is followed by an operator or ).
            if(is_operator(stack.top()) || (stack.top() == ")")) {
                cerr << "Error: equation has an illegal expression " << term << " " << stack.top() << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
            // ( exists without ).
            if(++brackets > 0) {
                cerr << "Error: unpaired parens" << endl;
                cerr << "Equation: " << m_equation << endl;
                exit(1);
            }
        }
        else { // It must be ) symbol.
            if(stack.size()) {
                // ) is followed by a number or (.
                if(is_number(stack.top()) || (stack.top() == "(")) {
                    cerr << "Error: equation has an illegal expression " << term << " " << stack.top() << endl;
                    cerr << "Equation: " << m_equation << endl;
                    exit(1);
                }
            }
            brackets--;
        }

        // The term has passed all error-checking conditions. Push it to the solver stack.
        stack.push(term);
    }
    // Check if parens have correct pairs.
    if(brackets) {
        cerr << "Error: unpaired parens" << endl;
        cerr << "Equation: " << m_equation << endl;
        exit(1);
    }
    // Equation does not start with a number or (.
    if(!is_number(stack.top()) && (stack.top() != "(")) {
        cerr << "Error: equation starts with an illegal expression " << stack.top() << endl;
        cerr << "Equation: " << m_equation << endl;
        exit(1);
    }
}

// Print the contents of solver stack.
void solver_t::print() const {
    cout << "Stack [" << stack.size() << "]: ";
    stack.print();
}

// Reset the solver stack.
void solver_t::reset() { stack.clear(); }

