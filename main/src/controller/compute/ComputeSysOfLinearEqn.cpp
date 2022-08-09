/**
 * @author Michael Dias
 * @file ComputeSysOfLinearEqn.cpp
 * @brief Concrete compute class for SLE. 
 * @details Overrides the solve function in Compute that is meant for computing Systems of Linear Equations 
 * @version 1.0
 * @date 2021-11-23
 */

#include "../../../include/controller/compute/ComputeSysOfLinearEqn.h"
#include "../../../include/model/analyser/Lexer.h"
#include "../../../include/model/analyser/Parser.h"
#include "../../../include/model/analyser/Interpreter.h"
#include <iostream>

/**
 * @brief function to take a set of linear equations and get solutions to the system of linear equations
 * @param equations the equations of the system
 * @return the solutions to the system of linear equations
 */
std::vector<std::string> ComputeSysOfLinearEqn::solve(const std::vector<std::string>& equations) const {
    try {
        std::vector<Node *> trees;
        for (const std::string &equation: equations) {
            Lexer lexer(equation);
            Parser parser = Parser();
            parser.createParseTree(lexer.tokenizer());
            trees.push_back(parser.getRoot());
        }

        Interpreter interpreter(trees);

        std::vector<char> variable_names = interpreter.getVariableNames();
        //Create list of possible parameter names (alphabet - elements of variable_names)
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        std::vector<char> possible_parameter_names;
        for (char c: alphabet) {
            if (!(std::find(variable_names.begin(), variable_names.end(), c) != variable_names.end()))
                possible_parameter_names.push_back(c);
        }

        std::vector<int> basic_var_indeces;
        std::vector<std::string> output;

        // Get 2D vector representing RREF of the system of linear equations
        Matrix augmented_matrix = Matrix(interpreter.getAugmentedMatrix());
        augmented_matrix.reduceToRREF();
        std::vector<std::vector<double>> solution_matrix = augmented_matrix.getValues();

        // Check for system inconsistency
        bool all_coefficients_0;
        for (int i = 0; i < solution_matrix.size(); i++) {
            all_coefficients_0 = true;
            for (int j = 0; j < solution_matrix[0].size() - 1; j++) {
                if (solution_matrix[i][j] != 0) {
                    all_coefficients_0 = false;
                    break;
                }
            }
            if (all_coefficients_0 && solution_matrix[i][solution_matrix[0].size() - 1]) {
                // System is inconsistent
                output.push_back("There are no solutions for the given system");
                return output;
            }
        }

        // System is consistent
        // Find which columns/variables to parameterise
        for (int i = 0; i < solution_matrix.size(); i++) {
            //for each row find the leading 1. record the row and column of the leading 1
            for (int j = 0; j < solution_matrix[0].size() - 1; j++) {
                if (solution_matrix[i][j] == 1) {
                    basic_var_indeces.push_back(j);
                    break;
                }
            }
        }

        // Assign a parameter to appropriate variables
        std::map<int, char> parameters;
        for (int i = 0; i < solution_matrix[0].size() - 1; i++) {
            // Does current column represent a variable to be parameterised
            if (!(std::find(basic_var_indeces.begin(), basic_var_indeces.end(), i) != basic_var_indeces.end())) {
                // Map column number to parameter name
                parameters.insert(std::pair<int, char>(i, possible_parameter_names.back()));
                possible_parameter_names.pop_back();
            }
        }

        // For each column get the variable it represets in terms of params
        std::string current_line;
        std::string coeff;
        std::string constant;
        int position = 0;
        int which_row = 0;
        int which_param;
        for (int i = 0; i < solution_matrix[0].size() - 1; i++) {
            current_line = "";
            //Is the current column representing a non free variable
            if (std::find(basic_var_indeces.begin(), basic_var_indeces.end(), i) != basic_var_indeces.end()) {
                which_param = 0;
                current_line.push_back(variable_names[i]);
                current_line.append(" = ");

                for (int j = i + 1; j < solution_matrix[0].size() - 1; j++) {
                    if (solution_matrix[which_row][j] != 0) {
                        // Construct current_line
                        coeff = std::to_string(-solution_matrix[which_row][j]);
                        coeff.erase(coeff.find_last_not_of('0') + 1, std::string::npos);
                        if (coeff.back() == '.') coeff.pop_back();
                        if (coeff != "1")
                            current_line.append(coeff);
                        current_line.push_back(parameters[j]);
                        current_line.append(" + ");
                        which_param++;
                    }
                }
                constant = std::to_string(solution_matrix[which_row].back());
                constant.erase(constant.find_last_not_of('0') + 1, std::string::npos);
                if (constant.back() == '.') constant.pop_back();
                if (constant != "0")
                    current_line.append(constant);  ///append the constant
                which_row++;
            } else {
                current_line.push_back(variable_names[i]);
                current_line.append(" = ");
                current_line.push_back(parameters[i]);
            }
            output.push_back(current_line);
        }
        return output;
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}


