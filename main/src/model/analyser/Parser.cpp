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

#include "../../../include/model/analyser/Parser.h"
#include "../../../include/model/analyser/Lexer.h"

/**
 * @brief 
 * 
 * Initilaizes the parser to a root of null, seeing as no values have been added in right now
 * 
  */

Parser::Parser() {
    root = new Node(nullptr, nullptr);
}




/**
*   @brief returns the root for the parse tree
*   @return returns the root
*/
Node *Parser::getRoot() {
    return root;
}

/**
 * @brief gets the tokens for the equation passed in using lexer and begins the process for creating a parseTree by treating everything a subTree
*          after subTree has been creates, sets the root Node pointer to point to it
*
 * @param input -> the operation the user would like to peform
 */
void Parser::createParseTree(std::vector<Token> tokens) {
//    Lexer lexer = Lexer(input);
//    std::vector<Token> tokens = lexer.tokenizer();

    bool bracketDetected = false;

    //add error checker desribed in chat later

    Node *currentNode = root;
    Node *parseRoot;
    Token *t = &tokens[0];
    int startIndex;
    int endIndex;
    int bracketNum = 0;
    tie(root, t) = createSubTree(t);

    if ((t - 1)->getType() != Token::Type::EOI) {
        std::string error = "Closing Bracket is Missing";
        throw std::runtime_error(error);
    }
}

/**
 * @brief 
 * 
 * The following creates a parser tree for a factorial number
 * 
 * @param t is the factorial used to create the tree
 * @return std::tuple<Node*, Token*> returns both the node and the current Token the tree ended on, for error checking purposes and linking the root node
 */

std::tuple<Node *, Token *> Parser::factorialSubTree(Token *t) {
    Node *sRoot = nullptr;

    int currentNum = std::stoi(t->value.substr(0, t->value.size() - 1));

    if (currentNum == 1) {
        return make_tuple(new Node(new Token(Token::Type::Number, std::to_string(currentNum), -1), nullptr), t);
    } else {
        sRoot = new Node(new Token(Token::Type::Mul, "*", -1), nullptr);
        sRoot->setLeft(new Node(new Token(Token::Type::Number, std::to_string(currentNum), -1), sRoot));

        Node *currentNode;
        Token *next;

        tie(currentNode, next) = factorialSubTree(
                new Token(Token::Type::Factorial, std::to_string(currentNum - 1) + "!", -1));

        sRoot->setRight(currentNode);
        currentNode->setParent(sRoot);

        return make_tuple(sRoot, t);
    }

}

/**
 * @brief 
 * Recursive function which goes through the parser trees and frees the nodes as a way of implementing garabage collection
 * @param r -> root node of the subTree that will be freed
 */
void Parser::freeTree(Node *r) {
    if (r == nullptr) {
        return;
    }

    if (r->isLeaf()) {
        free(r->getSpecialOp());
        free(r->getFunction());
        free(r->getValue());
        free(r);
        return;
    }


    freeTree(r->getLeft());

    freeTree(r->getRight());

    free(r->getSpecialOp());
    free(r->getFunction());
    free(r->getValue());

    free(r);
}

/**
 * @brief 
 * 
 * creates a subTree for the parser tree
 * 
 * @param t is the token pointer used to create the tree, it is incremented by 1 every time the other token is added to the tree
 * @return std::tuple<Node*, Token*> returns both the node and the current Token the tree ended on, for error checking purposes and linking the root node to the sub tree root
 */
std::tuple<Node *, Token *> Parser::createSubTree(Token *t) {

    Node *sRoot = nullptr;
    Node *currentNode = sRoot;
    bool specialOpDetected = false;
    Token *specialOp = nullptr;

    Token *PrevOp = nullptr;


    while (t->value != ")") {

        if (t->getType() == Token::Type::EOI) {
            if (!(currentNode->getLeft() && currentNode->getRight()) &&
                (currentNode->getValue()->type != Token::Type::Number &&
                 currentNode->getValue()->type != Token::Type::Variable)) {
                std::string error = "Invalid Expression";
                throw std::runtime_error(error);
            }

            break;
        }

        //checks for an equals op and creates a different subtree
        if (t->value == "=") {
            if (t->value == "=") {
                Node *newRoot = new Node(t, nullptr);
                newRoot->setLeft(sRoot);
                sRoot->setParent(newRoot);
                sRoot = newRoot;
                currentNode = sRoot;
                PrevOp = t;
                t++;
                continue;
            }
        }

        if (t->type == Token::Type::Factorial) {
            Node *subRoot;

            tie(subRoot, t) = factorialSubTree(t);

            if (PrevOp && (PrevOp->getType() == Token::Type::Plus || PrevOp->getType() == Token::Type::Minus) &&
                currentNode) {
                if (!currentNode->getLeft()) {
                    Node *newNode = new Node(new Token(Token::Type::Number, "0", -1), currentNode);
                    currentNode->setLeft(newNode);
                }

                if (!currentNode->getRight()) {
                    subRoot->setParent(currentNode);
                    currentNode->setRight(subRoot);
                }
            }

            if (!currentNode) {
                currentNode = subRoot;
                sRoot = subRoot;

            } else if (!currentNode->getLeft()) {
                subRoot->setParent(currentNode);
                currentNode->setLeft(subRoot);
                currentNode = subRoot;

            } else if (!currentNode->getRight()) {
                subRoot->setParent(currentNode);
                currentNode->setRight(subRoot);
                currentNode = subRoot;
            }
            PrevOp = t;
            t++;
            continue;
        }

        if (t->getType() == Token::Type::Trig || t->getType() == Token::Type::Log ||
            t->getType() == Token::Type::Sqrt || t->getType() == Token::Type::Diff) {
            specialOpDetected = true;
            specialOp = t;
            t++;
            continue;
        }

        if (t->value == "(") {
            Node *subRoot;

            if (specialOpDetected && PrevOp) {
                PrevOp = t - 1;
            } else {
                PrevOp = t;
            }

            tie(subRoot, t) = createSubTree(t + 1);

            if ((t - 1)->getType() == Token::Type::EOI) {
                std::string error = "Closing Bracket is Missing";
                throw std::runtime_error(error);
            }

            if (specialOpDetected) {
                specialOpDetected = false;

                if (specialOp->type == Token::Type::Sqrt) {
                    //convert square root to (^1/2)
                    Node *newNode = new Node(new Token(Token::Type::Power, "^", -1), nullptr);
                    newNode->setLeft(subRoot);
                    subRoot->setParent(newNode);
                    subRoot = newNode;

                    Node *current = subRoot;

                    newNode = new Node(new Token(Token::Type::Div, "/", -1), current);

                    newNode->setParent(current);
                    current->setRight(newNode);
                    current = newNode;

                    newNode = new Node(new Token(Token::Type::Number, "1", -1), current);

                    current->setLeft(newNode);
                    newNode->setParent(current);

                    newNode = new Node(new Token(Token::Type::Number, "2", -1), current);

                    current->setRight(newNode);
                    newNode->setParent(current);
                } else {
                    subRoot->setSpecialOp(specialOp);
                }
            }

            if (!currentNode) {
                sRoot = subRoot;
                currentNode = sRoot;
                subRoot->isSubR = true;
                continue;
            }

            if (!currentNode->getLeft()) {
                currentNode->setLeft(subRoot);
            } else {
                currentNode->setRight(subRoot);
            }

            subRoot->setParent(currentNode);

            subRoot->isSubR = true;

            currentNode = subRoot;
            continue;

        } else if (t->getType() == Token::Type::Variable || t->getType() == Token::Type::Number) {

            if (PrevOp && (PrevOp->getType() == Token::Type::Plus || PrevOp->getType() == Token::Type::Minus) &&
                currentNode) {
                if (!currentNode->getLeft()) {
                    Node *newNode = new Node(new Token(Token::Type::Number, "0", -1), currentNode);
                    currentNode->setLeft(newNode);
                }

                if (!currentNode->getRight()) {
                    Node *newNode = new Node(t, currentNode);
                    currentNode->setRight(newNode);
                    currentNode = newNode;
                }
            } else if (!currentNode) {
                sRoot = new Node(t, nullptr);
                currentNode = sRoot;
            } else if (!currentNode->getLeft()) {
                Node *newNode = new Node(t, currentNode);
                currentNode->setLeft(newNode);
                currentNode = newNode;

            } else if (!currentNode->getRight()) {
                Node *newNode = new Node(t, currentNode);
                currentNode->setRight(newNode);
                currentNode = newNode;
            }

        } else {
            while (true) {

                if (!currentNode) {
                    sRoot = new Node(t, nullptr);
                    currentNode = sRoot;
                    break;
                }

                if (!currentNode->getValue()) {
                    currentNode->setValue(t);
                    break;
                }

                if (PrevOp &&
                    !(PrevOp->getType() == Token::Type::Number || PrevOp->getType() == Token::Type::Variable ||
                      PrevOp->getType() == Token::Type::RParen || PrevOp->getType() == Token::Type::Factorial ||
                      PrevOp->getType() == Token::Type::Log || PrevOp->getType() == Token::Type::Trig ||
                      PrevOp->getType() == Token::Type::LParen)) {

                    if (t->getType() == Token::Type::Plus || t->getType() == Token::Type::Minus) {

                        if (!currentNode->getLeft()) {
                            Node *newNode = new Node(new Token(Token::Type::Number, "0", -1), currentNode);
                            currentNode->setLeft(newNode);
                        }

                        Node *newNode = new Node(t, currentNode);
                        currentNode->setRight(newNode);
                        currentNode = newNode;
                        break;

                    } else {
                        std::string error = "Invalid Expression";
                        throw std::runtime_error(error);
                    }
                }

                if (!currentNode->getParent()) {
                    Node *newNode = new Node(t, nullptr);
                    newNode->setLeft(currentNode);
                    sRoot = newNode;
                    currentNode->setParent(newNode);
                    currentNode = newNode;
                    break;
                }

                if (!currentNode->getParent()->getValue()) {
                    currentNode->getParent()->setValue(t);
                    currentNode = currentNode->getParent();
                    break;
                }

                if ((t->getType() < currentNode->getParent()->getValue()->getType()) &&
                    currentNode->getParent()->getValue()->value != "=" && !(t->getType() == Token::Type::Power &&
                                                                            currentNode->getParent()->getValue()->getType() ==
                                                                            Token::Type::Power) && t->position != -1) {
                    currentNode = currentNode->getParent();
                } else {
                    Node *newNode = new Node(t, currentNode->getParent());
                    newNode->setLeft(currentNode);
                    if (currentNode == currentNode->getParent()->getLeft()) {
                        currentNode->getParent()->setLeft(newNode);
                    } else {
                        currentNode->getParent()->setRight(newNode);
                    }
                    currentNode->setParent(newNode);
                    currentNode = newNode;
                    break;
                }
            }
        }

        PrevOp = t;
        t++;
    }
    return make_tuple(sRoot, t + 1);
}
