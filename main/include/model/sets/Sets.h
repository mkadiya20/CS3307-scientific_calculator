/**
 * @file Sets.h
 * @author Michael Dias & Michael Scantlebury
 * @brief This class provices methods for performing basic set operations
 * @version 0.1
 * @date 2021-12-01
 *
 */

#ifndef SETS_H
#define SETS_H

#include <vector>
#include <string>
#include <algorithm>

class Sets{

    public:
        Sets() = default;
        ~Sets() = default;

        static std::vector<double> Union(std::vector<double> set1, const std::vector<double>& set2);
        static std::vector<double> intersection(std::vector<double> set1, std::vector<double> set2);
        static std::vector<double> Subtraction(std::vector<double> set1, std::vector<double> set2);
};

#endif