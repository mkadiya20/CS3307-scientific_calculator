/**
 * @brief This class creates and stores info on nodes used for the abstract syntax tree.
 *
 * @details This class stores info about the nodes within tree and allows other classes to traverse the tree through a pointer like system
 *
 * @author Michael Scantlebury
 * @version 1.0
 */


#ifndef NODE_H
#define NODE_H

#include <vector>
#include <iostream>
#include <string>

#include "../functions/Function.h"
#include "Token.h"


class Node {
private:
    Token *value;
    Node *left;
    Node *right;
    Node *parent;
    Token *specialOp;
    Function *function;
public:
    bool isSubR = false;
    bool reduced = false;

    explicit Node(Token *val, Node *p);

    explicit Node(const Node &n);

    ~Node() = default;

    Node *getLeft();

    Node *getRight();

    Token *getValue();

    Node *getParent();

    Token *getSpecialOp();

    Function *getFunction();

    void setLeft(Node *n);

    void setRight(Node *n);

    void setValue(Token *v);

    void setSpecialOp(Token *op);

    void clearSpecialOp();

    void setFunction(Function *f);

    void setParent(Node *n);

    bool isLeaf();

    void free();

    std::string toString();
};

#endif NODE_H

