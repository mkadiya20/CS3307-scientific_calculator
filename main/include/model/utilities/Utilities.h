/**
 * @brief This class contains some useful functions used in many places
 *
 * @details The Utilities class tests if 2 trees are equal and removes 0's off the ends of strings of decimals
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef GROUP29_UTILITIES_H
#define GROUP29_UTILITIES_H

#include "../analyser/Node.h"

class Utilities {
    public:
        Utilities() = default;
        ~Utilities() = default;
        static bool equalTrees(Node*, Node*);
        static std::string removeTrailingZeros(std::string num);
        static std::string removeTrailingZeros(double num);
};

#endif //GROUP29_UTILITIES_H
