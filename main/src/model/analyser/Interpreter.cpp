/**
 * @brief This class solves an Abstract Syntax Tree (AST).
 *
 * @details The Interpreter class takes an AST and reduces the
 * nodes by computing one operation at a time until one node remains.
 * The computation is carried out on the deepest internal node so that
 * the operation with highest precedence is done first.
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */


#include <string>
#include <cmath>

#include "../../../include/model/analyser/Interpreter.h"
#include "../../../include/model/analyser/Token.h"
#include "../../../include/model/analyser/Parser.h"
#include "../../../include/model/functions/Fraction.h"
#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/functions/Factorial.h"
#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Log.h"
#include "../../../include/model/functions/Polynomial.h"

using namespace std;

/**
 * parameterised constructor
 * @param ast the root node of the Abstract Syntax Tree (AST)
 */
Interpreter::Interpreter(Node *ast) {
    Interpreter::maxDepth = 0;
    Interpreter::deepestInternalNode = nullptr;
    Interpreter::root = ast;
    groupFactorials(Interpreter::root);
    groupPolyFunctions(Interpreter::root);
    groupFunctions(Interpreter::root);
}


/**
 * parameterised constructor
 * @param trees the vector of AST trees
 */
Interpreter::Interpreter(std::vector<Node *> trees) {
    Interpreter::maxDepth = 0;
    Interpreter::deepestInternalNode = nullptr;
    Interpreter::trees = trees;
    for (Node *tree: trees) {
        groupFactorials(tree);
        groupPolyFunctions(tree);
        groupFunctions(tree);
        searchLinearEquation(tree);
    }
}


/**
 * locates the deepest node using infix order
 * @param node the root node to recursively search
 * @param depth the current depth of the node
 */
void Interpreter::setDeepestNode(Node *node, int depth) {
    if (node != nullptr && !node->reduced) {
        // search the left subtree for deepest node
        setDeepestNode(node->getLeft(), depth + 1);

        // check if the current depth is the greatest so far
        if (maxDepth <= depth) {
            maxDepth = depth;
            deepestInternalNode = node;
        }

        // search the right subtree for deepest node
        setDeepestNode(node->getRight(), depth + 1);
    }
}


/**
 * group all the factorials in the tree by calculating the
 * factorials and turning them into numbers
 * @param node the tree to check for factorials
 */
void Interpreter::groupFactorials(Node *node) {
    if (node == nullptr) {
        return;
    }
    // do a prefix search, check if there is a special operation
    Token *token = node->getValue();

    if (token->getType() == Token::Type::Factorial) {
        int f = stoi(token->value, nullptr);
        long ans = Factorial::factorial(f);
        auto *t = new Token(Token::Type::Number, to_string(ans), -1);
        node->setValue(t);
    }

    groupFunctions(node->getLeft());
    groupFunctions(node->getRight());
}

/**
 *  group all the functions in the tree by check its special
 *  operation token
 * @param node the tree to check for functions
 */
void Interpreter::groupFunctions(Node *node) {
    if (node == nullptr) {
        return;
    }
    // do a prefix search, check if there is a special operation
    Token *specialOp = node->getSpecialOp();

    Token *token = node->getValue();

    if (specialOp && specialOp->getType() == Token::Type::Trig) {
        Function *f = new Trig(node, specialOp->value, 1, 1);
        node->setFunction(f);
    }

    if (specialOp && specialOp->getType() == Token::Type::Log) {
        // default base 10 is passed
        Function *f = new Log(node, 10, 1, 1);
        node->setFunction(f);
    }

    // if the value is a Number, create a constant Function
    if (token->getType() == Token::Type::Number) {
        // if specialOp exists, create a new function
        if (specialOp && specialOp->getType() == Token::Type::Trig) {
            Function *f = new Trig(stod(token->value, nullptr), specialOp->value, 1, 1);
            node->setFunction(f);
        } else if (specialOp && specialOp->getType() == Token::Type::Log) {
            // default base 10 is passed
            Function *f = new Log(stod(token->value, nullptr), 10, 1, 1);
            node->setFunction(f);
        } else {
            Function *f = new Constant(stod(token->value, nullptr));
            node->setFunction(f);
        }
        node->reduced = true;
    }

    groupFunctions(node->getLeft());
    groupFunctions(node->getRight());
}


/**
 * group all the polynomials in tree by searching for
 * the pattern c*x^n
 * @param node the tree to check for polynomials
 */
void Interpreter::groupPolyFunctions(Node *node) {
    if (node == nullptr) {
        return;
    }

    if (node->getValue()->getType() == Token::Type::Mul && node->getLeft() &&
        node->getRight() && node->getRight()->getLeft() && node->getRight()->getRight()) {
        // check if left child is a number token (coefficient)
        bool flag = true;
        if (node->getLeft()->getValue()->getType() != Token::Type::Number) {
            flag = false;
        }

        // check right for power(^) token
        if (node->getRight()->getValue()->getType() != Token::Type::Power) {
            flag = false;
        }

        // check right->left for variable token
        if (node->getRight()->getLeft()->getValue()->getType() != Token::Type::Variable) {
            flag = false;
        }

        // check right->right for a number token (exponent)
        if (node->getRight()->getRight()->getValue()->getType() != Token::Type::Number) {
            flag = false;
        }

        if (flag) {
            double coefficient = stod(node->getLeft()->getValue()->value, nullptr);
            char variable = node->getRight()->getLeft()->getValue()->value[0];
            int power = stoi(node->getRight()->getRight()->getValue()->value, nullptr);

            auto *p = new Polynomial(coefficient, variable, power);
            Function *f = p;
            node->setFunction(f);
            node->setValue(new Token(Token::Type::Polynomial, p->toString(), -1));
            node->setLeft(nullptr);
            node->setRight(nullptr);
            node->reduced = true;
        }
    }

    if (node->getValue()->getType() == Token::Type::Variable) {
        auto *p = new Polynomial(1, node->getValue()->value[0], 1);
        Function *f = p;
        node->setFunction(f);
        node->setValue(new Token(Token::Type::Polynomial, p->toString(), -1));
        node->setLeft(nullptr);
        node->setRight(nullptr);
        node->reduced = true;
    }

    groupPolyFunctions(node->getLeft());
    groupPolyFunctions(node->getRight());
}


/**
 * reduce the AST by solving the operation on the deepest internal node.
 */
void Interpreter::reduce() {
    // reset the values
    maxDepth = 0;
    deepestInternalNode = nullptr;

    // set the deepest node
    setDeepestNode(root, 0);

    // get two children nodes of internal node and its value
    Node *left = deepestInternalNode->getLeft();
    Node *right = deepestInternalNode->getRight();
    Token *token = deepestInternalNode->getValue();

    // get the functions from the nodes
    Function *f1 = left->getFunction();
    Function *f2 = right->getFunction();
    Function *f3 = nullptr;

    // stores the string of double value after computation
    string value;

    // try-catch for any arithmetic errors or undefined behaviour
    try {
        if (!f1 || !f2) {
            value = deepestInternalNode->getValue()->value;
        } else {
            // if the internal node is =
            if (Token::Type::Equal == token->getType()) {
                // if right child is a constant, do not reduce
                if (deepestInternalNode->getRight()->getFunction()->getType() == "Constant") {
                    deepestInternalNode->reduced = true;
                    return;
                }

                auto *t = new Token(Token::Type::Minus, "-", -1);
                Node *minusNode = new Node(t, deepestInternalNode);
                minusNode->reduced = false;
                minusNode->setLeft(deepestInternalNode->getLeft());
                minusNode->setRight(deepestInternalNode->getRight());
                deepestInternalNode->setLeft(minusNode);

                auto *t2 = new Token(Token::Type::Number, "0", -1);
                Node *zeroConstant = new Node(t2, deepestInternalNode);

                zeroConstant->reduced = true;
                deepestInternalNode->setRight(zeroConstant);

                return;
            }


            // if the internal node is +, add two leaf nodes
            if (Token::Type::Plus == token->getType()) {
                f3 = *f1 + *f2;
                // if function is null, it is already reduced
                if (f3) {
                    value = f3->toString();
                } else {
                    value = deepestInternalNode->getValue()->value;
                }
            }

            // if the internal node is -, subtract two leaf nodes
            if (Token::Type::Minus == token->getType()) {
                f3 = *f1 - *f2;
                // if function is null, it is already reduced
                if (f3) {
                    value = f3->toString();
                } else {
                    value = deepestInternalNode->getValue()->value;
                }
            }

            // if the internal node is *, multiply two leaf nodes
            if (Token::Type::Mul == token->getType()) {
                f3 = *f1 * *f2;
                // if function is null, it is already reduced
                if (f3) {
                    value = f3->toString();
                } else {
                    value = deepestInternalNode->getValue()->value;
                }
            }

            // if the internal node is /, divide two leaf nodes
            if (Token::Type::Div == token->getType()) {
                f3 = new Fraction(f1, f2);
                dynamic_cast<Fraction *>(f3)->simplify();
                // if function is null, it is already reduced
                if (f3) {
                    value = f3->toString();
                } else {
                    value = deepestInternalNode->getValue()->value;
                }
            }

            // if the internal node is ^, get left^right
            if (Token::Type::Power == token->getType()) {
                f3 = f1->pow(f2);
                // if function is null, it is already reduced
                if (f3) {
                    value = f3->toString();
                } else {
                    value = deepestInternalNode->getValue()->value;
                }
            }
        }
    } catch (exception &e) {
        // catch any error and throw it again
        string error = "Error in calculation";
        throw std::runtime_error(error + e.what());
    }

    Token *t = nullptr;

    // if node has a special op, this is the root node of the internal function
    if (deepestInternalNode->getSpecialOp()) {
        if (f3 && f3->isInputConstant()) {
            deepestInternalNode->getFunction()->setValue(f3->getValue());
        }
    } else {
        deepestInternalNode->setFunction(f3);
    }

    if (auto *f = deepestInternalNode->getFunction()) {
        // make a new number token
        if (f->getType() == "Trig") {
            t = new Token(Token::Type::Trig, value, -1);
        } else if (f->getType() == "Log") {
            t = new Token(Token::Type::Log, value, -1);
        } else if (f->getType() == "Polynomial") {
            t = new Token(Token::Type::Polynomial, value, -1);
        } else {
            t = new Token(Token::Type::Number, value, -1);
        }
    } else {
        t = new Token(deepestInternalNode->getValue()->getType(), value, -1);
    }

    // remove the leaf nodes, change value to the computed number
    deepestInternalNode->setValue(t);

    if (f3) {
        deepestInternalNode->setLeft(nullptr);
        deepestInternalNode->setRight(nullptr);
    }
    deepestInternalNode->reduced = true;
}


/**
 * simplify the trig or log functions of constant inner functions
 */
void Interpreter::simplify() const {
    Token *specialOp = root->getSpecialOp();
    Token *token = root->getValue();
    // if specialOp is a trig, solve the trig function
    if ((Token::Type::Trig == specialOp->getType() || Token::Type::Log == specialOp->getType()) &&
        root->getFunction()->isInputConstant()) {
        double val = root->getFunction()->getValue();
        Function *c = new Constant(val);
        root->setFunction(c);
        root->setValue(new Token(Token::Type::Number, Utilities::removeTrailingZeros(val), -1));
        root->clearSpecialOp();
    }
}


/**
 * completely reduce the expression and get the string of each step
 * @return the vector of steps for each reduction
 */
std::vector<string> Interpreter::getSteps() {
    std::vector<string> steps;

    int stepCount = 1;
    string step;

    // add the initial expression
    step = "Expression: " + root->toString();
    steps.push_back(step);


    // loop until there is only one node remaining
    while (!root->reduced && !root->isLeaf()) {
        reduce();
        step = root->toString();
        if (steps.back() != step) {
            steps.push_back(step);
        }
        stepCount++;
    }
    if (root->isLeaf() && root->getSpecialOp() && root->getFunction()->isInputConstant()) {
        simplify();
        step = root->toString();
        if (steps.back() != step) {
            steps.push_back(step);
        }
        steps.push_back(step);
        stepCount++;
    }

    if (steps.size() == 1) {
        steps.push_back(root->toString());
        stepCount++;
    }

//    string answer = steps.back();
//    string result;
//    steps.pop_back();
//
//    size_t pos = answer.find('/');
//    // if the answer is a fraction turn that into a double
//    if (pos == 1) {
//        string num = answer.substr(0, pos);
//        string denom = answer.substr(pos + 1);
//
//        double numerator = stod(num, nullptr);
//        double denominator = stod(denom, nullptr);
//
//        // return the double value of the fraction
//        result = Utilities::removeTrailingZeros(numerator / denominator) + " or " + answer;
//    }
//
//    // if answer is double turn into fraction
//    else {
//        double ans = stod(answer, nullptr);
//        Function *c = new Constant(ans);
//        Function *fraction = Fraction::to_fraction(c);
//
//        result = answer + " or " + fraction->toString();
//    }
//
//    steps.push_back(result);

    return steps;
}


/**
 * solves the root tree and returns the final value.
 * Input tree is guaranteed to return a constant value.
 * @return the constant value of the function
 */
double Interpreter::solve() {
    std::vector<std::string> result = getSteps();
    string answer = result.back();

    size_t pos = answer.find('/');
    // if the answer is a fraction turn that into a double
    if (pos == 1) {
        string num = answer.substr(0, pos);
        string denom = answer.substr(pos + 1);

        double numerator = stod(num, nullptr);
        double denominator = stod(denom, nullptr);

        // return the double value of the fraction
        return numerator / denominator;
    } else {
        return stod(answer, nullptr);
    }
}


/**
 * get the vector of variable names for linear equations
 * @return the vector of variables
 */
vector<char> Interpreter::getVariableNames() {
    vector<char> variableNames;

    for (auto const &currEquation: map) {
        char variable = currEquation.first;
        if (variable != 'C') {
            variableNames.push_back(variable);
        }
    }

    return variableNames;
}


/**
 * get the augmented matrix from the linear equations
 * @return a vector of vector for double values
 */
vector<vector<double>> Interpreter::getAugmentedMatrix() {
    int i = 0, j = 0;
    int rows = map['C'].size();
    int cols = map.size();
    vector<vector<double>> matrix(rows, vector<double>(cols));
    for (auto const &currEquation: map) {
        i = 0;
        vector<double> coefs = currEquation.second;
        for (double &coef: coefs) {
            matrix.at(i).at(j) = coef;
            i++;
        }
        j++;
    }
    return matrix;
}


/**
 * search the tree for a linear equation and store the
 * coefficients and the variables in a hashmap.
 * @param node the tree to search for linear equation
 */
void Interpreter::searchLinearEquation(Node *node) {
    if (!node) {
        return;
    }

    searchLinearEquation(node->getRight());
    searchLinearEquation(node->getLeft());

    if (node->getValue()->getType() == Token::Type::Polynomial) {
        double coef = node->getFunction()->getCoef();
        char variable = dynamic_cast<Polynomial *>(node->getFunction())->getVariable();
        if (map.count(variable)) {
            map[variable].push_back(coef);
        } else {
            vector<double> v;
            v.push_back(coef);
            map[variable] = v;
        }
    }

    if (node->getValue()->getType() == Token::Type::Number) {
        double coef = node->getFunction()->getCoef();
        char variable = 'C';
        if (map.count(variable)) {
            map[variable].push_back(coef);
        } else {
            vector<double> v;
            v.push_back(coef);
            map[variable] = v;
        }
    }

}