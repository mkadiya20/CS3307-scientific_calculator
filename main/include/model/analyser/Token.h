/**
 * @brief This class represents a token
 *
 * @details This class represents a token of various types along with
 * its value in a string form and its position in the given input string.
 * This class is used by the lexer to generate a set of tokens from the
 * input string and by the parser to create parse trees.
 *
 * @author Mihir Kadiya
 */


#ifndef CS3307_TOKEN_H
#define CS3307_TOKEN_H

#include <string>

class Token {
public:
    enum class Type {
        Number,
        Equal,
        Plus,
        Minus,
        Div,
        Mul,
        Power,
        LParen,
        RParen,
        Polynomial,
        Trig,
        Log,
        Sqrt,
        Diff,
        Variable,
        Factorial,
        EOI
    };

    Token(Type type, std::string value, int position);

    ~Token() = default;

    Type getType() const;

    void setType(Type type);

    bool equals(Type type) const;

    Token(const Token &t);

    Type type;
    std::string value;
    int position;
};


#endif //CS3307_TOKEN_H
