/**
 * @file Sets.h
 * @author Michael Dias & Michael Scantlebury
 * @brief This class provices methods for performing basic set operations
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 */

#include "../../../include/model/sets/Sets.h"

/**
 * @brief takes two sets and returns a set that contains all elements from both sets
 * 
 * @param set1 the first set
 * @param set2 the second set
 * @return the union of the first and second sets 
 */
std::vector<double> Sets::Union(std::vector<double> set1, const std::vector<double>& set2) {
    std::vector<double> newSet = set1;
    
    for (double n : set2) {
        if (!(std::find(set1.begin(), set1.end(), n) != set1.end())) {
            newSet.push_back(n);
        }
    }

    return newSet;
}

/**
 * @brief takes two sets and returns a set containing elements that are common to both sets
 * 
 * @param set1 the first set
 * @param set2 the second set
 * @return the intersection of the first and second sets 
 */
std::vector<double> Sets::intersection(std::vector<double> set1, std::vector<double> set2) {
    
    std::vector<double> newSet;
    
    for (double n : set2) {
        if ((std::find(set1.begin(), set1.end(), n) != set1.end())) {
            newSet.push_back(n);
        }
    }

    return newSet;
}

/**
 * @brief takes two sets and returns a set containing elements that are in the first set and not the second set
 * 
 * @param set1 the first set
 * @param set2 the second set
 * @return the intersection of the first and second sets 
 */
std::vector<double> Sets::Subtraction(std::vector<double> set1, std::vector<double> set2) {
    
    std::vector<double> newSet;
    
    for (double n : set1) {
        if (!(std::find(set2.begin(), set2.end(), n) != set2.end())) {
            newSet.push_back(n);
        }
    }

    return newSet;
}
