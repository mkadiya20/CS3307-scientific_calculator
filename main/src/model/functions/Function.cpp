/**
 * @brief This class is the parent class of all functions
 *
 * @details The Function class is used as a parent of all types of functions, storing shared information of functions
 * and allowing operations between different functions to be handled through overrided methods
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include "../../../include/model/functions/Function.h"

using namespace std;

Function::Function() = default;

/**
 * returns the type of equation
 * @return type The type of function
 */
std::string Function::getType() {
    return type;
}

/**
 * operator overload for +
 * @param p1 the first function
 * @param p2 the second function
 * @return the function after addition
 */
Function *operator+(Function &f1, Function &f2) {
    return f1.add(&f2);
}

/**
 * operator overload for +
 * @param p1 the first function
 * @param p2 the second function
 * @return the function after subtraction
 */
Function *operator-(Function &f1, Function &f2) {
    return f1.subtract(&f2);
}

/**
 * operator overload for +
 * @param p1 the first function
 * @param p2 the second function
 * @return the function after multiplication
 */
Function *operator*(Function &f1, Function &f2) {
    return f1.multiply(&f2);
}