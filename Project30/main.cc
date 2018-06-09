#include <iostream>

#include "file_handler.h"
#include "solver.h"

using namespace std;

int main(void) {
    file_handler_t file_equations;  // Input file handler for equations
    string input_set;               // Input data set
    solver_t solver;                // Postfix equation solver



    /**********************************************************
     * TEST YOUR CODE HERE TO SEE IF THE POSTFIX SOLVER WORKS *
     **********************************************************/
    solver.parse("2+-3*5");     // An equation to test
    solver.print();             // Print the parsed equation stored in the solver stack.
    solver.convert_to_postfix();// Convert the infix to postfix equation.
    solver.print();             // Print postfix expression stored in the solver stack.
    solver.calculate();         // Calculate the postfix equation.
    solver.print();             // Print the final answer stored in the solver stack.
    solver.reset();             // Make it ready for another calculation.

    solver.parse("(-2+3)*5");
    solver.print();
    solver.convert_to_postfix();
    solver.print();
    solver.calculate();
    solver.print();
    solver.reset();

    solver.parse("-4*((2.5+-3.5)+5.1)");
    solver.print();
    solver.convert_to_postfix();
    solver.print();
    solver.calculate();
    solver.print();
    solver.reset();
    /********************
     * END OF TEST CODE *
     ********************/

    

    // Get the input set: last two digits of student ID.
    while(input_set.empty()) {
        cout << endl << "Last digit of your student ID: ";
        cin >>  input_set;
        if((input_set.find_first_not_of("0123456789") != string::npos) ||
           (input_set.size() > 1)) {
            cout << "Invalid digit " << input_set << endl;
            input_set.clear();
        }
    }
    file_equations.read("inputs/"+input_set+"/equations.data");
    
    cout << endl << "Calculating " << file_equations.size() << " equations:" << endl;
    for(size_t i = 0; i < file_equations.size(); i++) {
        solver.reset();
        solver.parse(file_equations.get(i));
        solver.convert_to_postfix();
        solver.calculate();
        solver.print();
    }
    cout << endl << "Postfix solver done." << endl;
	system("pause");
    return 0;
}

