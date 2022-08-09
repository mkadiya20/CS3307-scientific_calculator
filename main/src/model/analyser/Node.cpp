/**
 * @brief This class creates and stores info on nodes used for the abstract syntax tree.
 *
 * @details This class stores info about the nodes within tree and allows other classes to traverse the tree through a pointer like system
 *
 * @author Michael Scantlebury
 * @version 1.0
 */

#include <iostream>
#include <string>

#include "../../../include/model/analyser/Node.h"

/**
 * @brief Construct a new Node
 * 
 * @param val -> the token value of the node
 * @param p  -> a pointer to the parent of the node
 */
Node::Node(Token* val, Node* p) {
    value = val ? new Token(*val) : nullptr;
    parent = p;
    left = nullptr;
    right = nullptr;
    specialOp = nullptr;
    function = nullptr;
}

/**
 * @brief Construct a new Node from an existing on
 * 
 * @param n -> the memory address of the node
 */
Node::Node(const Node &n) {
    value = n.value;
    parent = n.parent;
    left = n.left;
    right = n.right;
    specialOp = nullptr;
    function = nullptr;
}

/**
 * @brief get the node stored left of this node
 * 
 * @return return the node stored left of this node
 */
Node* Node::getLeft() {
    return left;
}

/**
 * @brief get the node stored right of this node
 * 
 * @return return the node stored right of this node
 */
Node* Node::getRight() {
    return right;
}

/**
 * @brief get the value stored in this node
 * 
 * @return get the value stored in this node
 */
Token* Node::getValue() {
    return value;
}

/**
 * @brief get the Node stored in the node
 * 
 * @return return the Node stored in the node
 */
Node* Node::getParent() {
    return parent;
}

/**
 * @brief get the Node stored in the node
 * 
 * @return return the Node stored in the node
 */
Token* Node::getSpecialOp() {
    return specialOp;
}


/**
 * @brief get the Function stored in the Node
 * 
 * @return return the Function stored in the Node
 */
Function* Node::getFunction() {
    return function;
}

/**
 * @brief set the Left node stored in the Node
 * 
 * @param n left node to stored in the node
 */
void Node::setLeft(Node *n) {
    left = n;
}


/**
 * @brief set the right node stored in the Node
 * 
 * @param n right node to stored in the node
 */
void Node::setRight(Node *n) {
    right = n;
}


/**
 * @brief set the Token stored in the Node
 * 
 * @param n the token to be stored
 */
void Node::setValue(Token *v) {
    this->value = new Token(*v);
}

/**
 * @brief set the special op stored in the node
 * 
 * @param op the special op to set
 */
void Node::setSpecialOp(Token *op) {
    this->specialOp = new Token(*op);
}

/**
 * @brief remove the special OP
 * 
 */
void Node::clearSpecialOp () {
    this->specialOp = nullptr;
}

/**
 * @brief set the Function stored in the node
 * 
 * @param f the function to set
 */
void Node::setFunction(Function *f) {
    this->function = f;
}

/**
 * @brief set the parent stored in the node
 * 
 * @param the node to set
 */
void Node::setParent(Node *n) {
    parent = n;
}

/**
 * @brief check if the node is a leaf
 * 
 * @return return true of false
 */
bool Node::isLeaf() {

    if (!getLeft() && !getRight()) {
        return true;
    }

    return false;
}


/**
 * covert the AST to string representation
 * @param node the root node containing the expression
 * @return the string representation of the AST
 */
std::string Node::toString() {
    std::string result;

    // sin(cos(30) + tan(60))
    if (getSpecialOp()) {
        if (getFunction()) {
            result += getFunction()->toString();
        } else {
            result += this->getValue()->value;
        }
    } else {
        if (this->getLeft()) {
            result += this->getLeft()->toString();
        }

        if (getFunction()) {
            result += getFunction()->toString(); // 1*cos(
        } else {
            result += this->getValue()->value;
        }

        if (this->getRight()) {
            result += this->getRight()->toString();
        }
    }

    return result;
}