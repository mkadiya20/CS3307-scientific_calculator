/**
 * @file History.h
 * @author Mihir Kadiya
 * @brief
 *
 * This is a singleton class as there can only be
 * one instance of history. The class uses a hashmap
 * to store the pointers of vectors of string objects and uses
 * the size of the map as an index. The size is incremented
 * after inserting in the hashmap.
 *
 * @version 1.0
 */

#ifndef ASSIGNMENT_1_HISTORY_H
#define ASSIGNMENT_1_HISTORY_H

#include <unordered_map>
#include <iostream>
#include <utility>
#include <vector>


class History {
public:
    static History &getInstance();

    ~History() = default;

    void logHistory(std::vector<std::string> steps);

    std::vector<std::string> retrieveHistory(int index);

    int size() const;

private:
    std::unordered_map<int, std::vector<std::string>> historyMap;
    int length;

    History() {
        length = 0;
    }

};


#endif
