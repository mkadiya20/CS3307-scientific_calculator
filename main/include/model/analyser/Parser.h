/**
 * @brief This class creates an Abstract Syntax Tree (AST).
 *
 * @details The Parser takes a string and with the help of the lexer, gets a list of tokens which it then uses to create a parser tree out of
 *          This tree is a representation of the problem passed in by the user and using bedmas as a grammar to order the equations such that 
 *          The interpreter may solve the equations.
 *
 * @author Michael Scantlebury
 * @version 1.0
 */

#ifndef CS3307_PARSER_H
#define CS3307_PARSER_H

#include "Node.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "../../../include/model/analyser/Token.h"

using namespace std;

class Parser {
private:
    Node *root;

    std::tuple<Node *, Token *> factorialSubTree(Token *t);

    void freeTree(Node *r);

protected:
    std::tuple<Node *, Token *> createSubTree(Token *t);

public:
    Parser();

    void createParseTree(std::vector<Token> tokens);

    Node *getRoot();

};


#endif //CS3307_PARSER_H