/**
 * @brief This class creates tokens out of the input string
 *
 * @details This class takes and input string and turns the different parts of it
 into tokens to represent different functions, variables, and operations
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include <stdexcept>
#include "../../../include/model/analyser/Lexer.h"

/**
 * constructor
 * @param inputExpr the user input expression
 */
Lexer::Lexer(std::string inputExpr) {
    expr = inputExpr;
    position = 0;
    currChar = expr[position];
}

/**
 * generate a list of tokens from the input expression
 * @return a list of tokens
 */
std::vector<Token> Lexer::tokenizer() {
    std::vector<Token> list;

    auto t = getNextToken();

    // keep getting tokens until the last EOF Token
    while (t.getType() != Token::Type::EOI) {

        if (t.getType() == Token::Type::Trig || t.getType() == Token::Type::Log) {
            if (list.size() > 1) {
                auto *prevToken = &list.back();
                if (prevToken && prevToken->getType() == Token::Type::Number) {
                    list.emplace_back(Token::Type::Mul, "*", -1);
                }
            }
        }
        // if current Token is a variable, check if last Token is an integer
        if (t.getType() == Token::Type::Variable) { //|| t.getType() == Token::Type::Trig) {
            // add a Mul Token in between, "2x" -> "(2*x", "2sin()" -> "(2*sin()"
            if (!list.empty() && list.back().getType() == Token::Type::Number) {
                // get the number token out of the vector
                auto prevToken = list.back();
                list.pop_back();
                // add a "(" token
                list.emplace_back(Token::Type::LParen, "(", -1);
                // add the number token back again
                list.emplace_back(prevToken);
                list.emplace_back(Token::Type::Mul, "*", -1);
            }

                // add "1" integer Token and a mul Token, "x" -> "(x", "sin()" -> "(sin()"
            else {
                list.emplace_back(Token::Type::LParen, "(", -1);
                list.emplace_back(Token::Type::Number, "1", -1);
                list.emplace_back(Token::Type::Mul, "*", -1);
            }

            // get next token and check if it is power token
            auto nextToken = getNextToken();

            // if it is a power token, add it in order and continue
            if (nextToken.getType() == Token::Type::Power) {
                list.emplace_back(t);
                list.emplace_back(nextToken);

                t = getNextToken();

                if (t.getType() == Token::Type::Number) {
                    // check if last token is power
                    auto prevToken = list.back();
                    list.pop_back();
                    if (prevToken.getType() == Token::Type::Power) {
                        // check if the last token is variable
                        auto pToken = list.back();
                        if (pToken.getType() == Token::Type::Variable) {
                            list.emplace_back(prevToken);
                            list.emplace_back(t);
                            list.emplace_back(Token::Type::RParen, ")", -1);

                            // get next token
                            t = getNextToken();
                        }
                    }
                } else {
                    list.erase(list.begin() + (list.size() - 6));
                }
                continue;
            }

                // add "^" and "1" to the back of variable, "x^1"
            else {
                // add the variable
                list.emplace_back(t);

                // add two tokens for "^" and "1"
                list.emplace_back(Token::Type::Power, "^", -1);
                list.emplace_back(Token::Type::Number, "1", -1);
                list.emplace_back(Token::Type::RParen, ")", -1);

                // if next token isn't EOI, add it that well
                if (nextToken.getType() != Token::Type::EOI) {
                    list.emplace_back(nextToken);
                }
                t = getNextToken();
                continue;
            }
        }

        list.push_back(t);
        t = getNextToken();
    }
    list.push_back(t);

    return list;
}

/**
 * get the next character in the string
 * if end of input is reached, set char to '\0'
 */
void Lexer::nextChar() {
    position++;

    if (position >= expr.length()) {
        currChar = '\0';
    } else {
        currChar = expr[position];
    }
}

/**
 * check if current character is a whitespace
 * @return true if it is a whitespace, false otherwise
 */
bool Lexer::isWhitespace() const {
    return currChar == ' ';
}

/**
 * check if current char is a digit
 * @return true if it is a digit, false otherwise
 */
bool Lexer::isDigit() const {
    switch (currChar) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
        default:
            return false;
    }
}

/**
 * check if current char is a variable
 * @return true if it is a variable, false otherwise
 */
bool Lexer::isVariable() const {
    switch (currChar) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
            return true;
        default:
            return false;
    }
}

/**
 * iterate the input and get the next Token
 * @return the next Token
 */
Token Lexer::getNextToken() {
    try {
        // keep looping till end of file
        while (currChar != '\0') {

            // if char is a whitespace, skip over it
            if (isWhitespace()) {
                nextChar();
                continue;
            }

            // if char is a digit, check for more consecutive digits (numbers)
            if (isDigit()) {
                return number_factorial();
            }

            // if char is a variable, check for more letters
            if (isVariable()) {
                return keyword();
            }

            // if char is '=', return the Token
            if (currChar == '=') {
                nextChar();
                return Token(Token::Type::Equal, "=", position - 1);
            }

            // if char is '+', return the Token
            if (currChar == '+') {
                nextChar();
                return Token(Token::Type::Plus, "+", position - 1);
            }

            // if char is '-', return the Token
            if (currChar == '-') {
                nextChar();
                return Token(Token::Type::Minus, "-", position - 1);
            }

            // if char is '*', return the Token
            if (currChar == '*') {
                nextChar();
                return Token(Token::Type::Mul, "*", position - 1);
            }

            // if char is '/', return the Token
            if (currChar == '/') {
                nextChar();
                return Token(Token::Type::Div, "/", position - 1);
            }

            // if char is '^', return the Token
            if (currChar == '^') {
                nextChar();
                return Token(Token::Type::Power, "^", position - 1);
            }

            // if char is '(', return the Token
            if (currChar == '(') {
                nextChar();
                return Token(Token::Type::LParen, "(", position - 1);
            }

            // if char is ')', return the Token
            if (currChar == ')') {
                nextChar();
                return Token(Token::Type::RParen, ")", position - 1);
            }

            // for any other case, return an error
            std::string error = "Character " + std::string(1, currChar) + " is invalid\n";

            // throw an error
            throw std::runtime_error(error);
        }

        // if end of file is reached, return the null Token
        return Token(Token::Type::EOI, "null", position);

    } catch (const std::exception &e) {
        throw std::runtime_error(e.what());
    }
}


/**
 * check for consecutive digits and return them as a Token
 * @return a number Token
 */
Token Lexer::number_factorial() {
    std::string result;

    // keep looping until EOF or next non-digit char
    while (currChar != '\0' && (isDigit() || currChar == '.')) {
        result += currChar;
        nextChar();
    }

    // if number ends with '.', it is invalid
    if (result.back() == '.') {
        throw std::runtime_error("Invalid number");
    }

    // check if the next char is !, return a factorial token instead
    if (currChar == '!') {
        result += currChar;
        nextChar();
        return Token(Token::Type::Factorial, result, (position - result.length()));
    }

    return Token(Token::Type::Number, result, (position - result.length()));
}


/**
 * check for consecutive characters
 * chars have to be trig names or single variables
 * @return a variable or trig Token
 */
Token Lexer::keyword() {
    std::string result;
    while (currChar != '\0' && isVariable()) {
        result += currChar;
        nextChar();
    }
    if (result == "sin" || result == "cos" || result == "tan") {
        return Token(Token::Type::Trig, result, (position - result.length()));
    } else if (result == "log") {
        return Token(Token::Type::Log, result, (position - result.length()));
    } else if (result == "sqrt") {
        return Token(Token::Type::Sqrt, result, (position - result.length()));
    } else if (result == "diff") {
        return Token(Token::Type::Diff, result, (position - result.length()));
    } else if (result.length() == 1) {
        return Token(Token::Type::Variable, result, position - 1);
    } else {
        throw std::runtime_error("Invalid variable name");
    }
}