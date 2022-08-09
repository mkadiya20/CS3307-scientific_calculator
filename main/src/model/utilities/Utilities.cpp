/**
 * @brief This class contains some useful functions used in many places
 *
 * @details The Utilities class tests if 2 trees are equal and removes 0's off the ends of strings of decimals
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include "../../../include/model/utilities/Utilities.h"


/**
 * check if both the trees have equal values
 * @param rootA the first tree
 * @param rootB the second tree
 * @return
 */
bool Utilities::equalTrees(Node *rootA, Node *rootB) {
    if(!rootA && !rootB) {
        return true;
    }
    else if (rootA && rootB && rootA->getValue()->value == rootB->getValue()->value) {
        if ((!rootA->getSpecialOp() && !rootB->getSpecialOp()) || (rootA->getSpecialOp() && rootB->getSpecialOp() &&
            rootA->getSpecialOp()->value == rootB->getSpecialOp()->value)) {
            bool equalLeft = equalTrees(rootA->getLeft(), rootB->getLeft());
            if (equalLeft) {
                return equalTrees(rootA->getRight(), rootB->getRight());
            } else {
                return false;
            }
        }
    }
    return false;
}

/**
 * removes any unnecessary trailing zeros from the string
 * @param num the string to check
 * @return the string without trailing zeros
 */
std::string Utilities::removeTrailingZeros(std::string num) {
    // if '.' is not found
    if (num.find('.') == std::string::npos) {
        return num;
    }

    std::string result = num;

    for (int i = num.length() - 1; i >= 0; i--) {
        if (num.at(i) == '0') {
            result = num.substr(0, i);
        } else if (num.at(i) == '.'){
            result = num.substr(0, i);
            return result;
        } else {
            return result;
        }
    }
    return result;
}

std::string Utilities::removeTrailingZeros(double num) {
    return removeTrailingZeros(std::to_string(num));
}
