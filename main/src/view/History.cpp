/**
 * @brief History class stores all the calculated expressions
 *
 * This is a singleton class as there can only be
 * one instance of history. The class uses a hashmap
 * to store the pointers of vectors of string objects and uses
 * the size of the map as an index. The size is incremented
 * after inserting in the hashmap.
 *
 * @author Mihir Kadiya
 */

#include "../../include/view/History.h"


/**
 * getter method for history instance
 * @return the history object
 */
History &History::getInstance() {
    static History instance;
    return instance;
}


/**
 * add the command pointer to hashmap
 * @param cmd the command pointer to add
 */
void History::logHistory(std::vector<std::string> steps) {
    historyMap[length] = std::move(steps);
    length++;
}


/**
 * get the command pointer from given index
 * @param index the index to get pointer from
 * @return the command pointer
 */
std::vector<std::string> History::retrieveHistory(int index) {
    return historyMap[index];
}


/**
 * getter method for size of the hashmap
 * @return the size of hashmap
 */
int History::size() const {
    return length;
}
