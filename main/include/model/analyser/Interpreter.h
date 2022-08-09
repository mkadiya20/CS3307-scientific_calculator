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

#ifndef CS3307_INTERPRETER_H
#define CS3307_INTERPRETER_H

#include <vector>
#include <unordered_map>
#include "../../../include/model/analyser/Node.h"

class Interpreter {
public:
    explicit Interpreter(Node *ast);

    explicit Interpreter(std::vector<Node *> trees);

    ~Interpreter() = default;

    std::vector<std::string> getSteps();

    double solve();

    std::vector<char> getVariableNames();

    std::vector<std::vector<double>> getAugmentedMatrix();

private:
    Node *deepestInternalNode;
    int maxDepth;
    Node *root;

    std::vector<Node *> trees;
    std::unordered_map<char, std::vector<double>> map;

    void setDeepestNode(Node *node, int depth);

    void groupFactorials(Node *node);

    void groupFunctions(Node *node);

    void groupPolyFunctions(Node *node);

    void reduce();

    void simplify() const;

    void searchLinearEquation(Node *);
};


#endif //CS3307_INTERPRETER_H
