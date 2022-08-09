/**
 * @author Created by Mihir Kadiya
 * @brief Concrete compute class
 * @details Overrides the solve function in Compute that is meant for computing Function values
 * @version 1.0
 * date 2021-11-30
 */

#include "../../../include/controller/compute/ComputeFunction.h"
#include "../../../include/model/analyser/Interpreter.h"
#include "../../../include/model/analyser/Lexer.h"
#include "../../../include/model/analyser/Parser.h"

/**
 * @brief gets a y value by computing a function at an input
 * @param function the function the use to compute a y value
 * @param input the x value (input to function)
 * @return the y value from function(input)
 */
double ComputeFunction::solve(const std::string& function, const std::string& input) {
    try {
        Lexer lexer(function);
        std::vector<Token> tokens = lexer.tokenizer();

        // substitute every variable token with a number token of value "input"
        for (Token &token: tokens) {
            if (token.getType() == Token::Type::Variable) {
                token = Token(Token::Type::Number, input, -1);
            }
        }

        Parser parser = Parser();
        parser.createParseTree(tokens);

        Interpreter interpreter = Interpreter(parser.getRoot());
        return interpreter.solve();
    } catch (exception &e) {
        throw std::runtime_error(e.what());
    }
}
