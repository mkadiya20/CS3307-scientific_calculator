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

#include "../../../include/model/analyser/Token.h"

Token::Token(Token::Type type, std::string value, int position) {
    Token::type = type;
    Token::value = value;
    Token::position = position;
}

Token::Token(const Token &n) {
    Token::type = n.type;
    Token::value = n.value;
    Token::position = n.position;
}

Token::Type Token::getType() const {
    return Token::type;
}

void Token::setType(Type type) {
    Token::type = type;
}

bool Token::equals(Type type) const {
    return Token::type == type;
}




