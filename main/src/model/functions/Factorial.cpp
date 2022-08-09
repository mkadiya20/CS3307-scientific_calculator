 /**
 * @brief This class stores a factorial
 *
 * @details The Factorial class simply solves factorial functions and turns them into a constant number
 *
 * @author Michael Dias
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include "../../../include/model/functions/Factorial.h"

/**
 * Takes a number and returns the factorial of it. Throws exception if factorial cannot be computed
 * @param input number to compute the factorial of
 * @return the factorial of the given number
 */

long Factorial::factorial(int input){
    if(input > 12)      //input to factorial is too large
        throw std::runtime_error("Input to factorial is too large");
    else if(input < 0)  //input to factorial can not be negative
        throw std::runtime_error("Input to factorial can not be negative");
    else if(input == 0) //factorial of 0 is 1 
        return 1;
    else{
        int running_total = input;
        for(int i = input - 1; i > 0; i--)
            running_total *= i;
        return running_total;
    }
}