/**
 * @file ComputeEquation.cpp
 * @author Michael Dias
 * @author Mihir Kadiya
 * @brief this class performs the steps necessary to solve an equation a
 * @version 1.0
 * @date 2021-11-30
 */


#include "../../../include/controller/compute/ComputeEquation.h"
#include "../../../include/model/analyser/Interpreter.h"
#include "../../../include/model/analyser/Parser.h"
#include "../../../include/model/analyser/Lexer.h"

/**
 * @brief implements an algorithm to solve a mathematical equation
 * 
 * @param equation the string representation of the equation to be solved
 * @return the solved equation
 */
std::vector<std::string> ComputeEquation::solve(const std::string& equation) const{
    try {
        Lexer lexer(equation);
        Parser parser = Parser();
        parser.createParseTree(lexer.tokenizer());
        Node *root = parser.getRoot();

        Interpreter i(parser.getRoot());

        std::vector<std::string> steps = i.getSteps();

        return steps;
    } catch (exception &e) {
        // catch any error and throw it again
        throw std::runtime_error(e.what());
    }
}