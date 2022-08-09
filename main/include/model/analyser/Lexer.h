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

#ifndef CS3307_LEXER_H
#define CS3307_LEXER_H

#include <vector>
#include <string>
#include "../../../include/model/analyser/Token.h"

class Lexer {
public:
    explicit Lexer(std::string inputExpr);
    ~Lexer() = default;
    std::vector<Token> tokenizer();

private:
    std::string expr;
    int position;
    char currChar;

    void nextChar();
    bool isWhitespace() const;
    bool isDigit() const;
    bool isVariable() const;
    Token getNextToken();

    Token number_factorial();
    Token keyword();
};


#endif //CS3307_LEXER_H
