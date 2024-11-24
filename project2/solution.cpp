#include "FileAVL.hpp"
#include "File.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Recursively traverses the FileAVL tree 
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
void queryRecursive(const size_t &min, const size_t &max, std::vector<File*> &result, Node* const &current) {
    // if the current node is null, return
    if (current == nullptr) {
        return;
    }
    // if the size of the files in the current node are less than min, return
    if (current->size_ < min) {
        return;
    }
    // if the size of the files in the current node are more than max, return
    if (current->size_ > max) {
        return;
    }

    // recurse on left
    queryRecursive(min, max, result, current->left_);
    // add all files in this node into result
    for (File* file : current->files_) {
        result.push_back(file);
    }
    // recurse on right
    queryRecursive(min, max, result, current->right_);
}

/**
 * @brief Retrieves all files in the FileAVL whose file sizes are within [min, max]
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @return std::vector<File*> storing pointers to all files in the tree within the given range.
 * @note If the query interval is in descending order (ie. the given parameters min >= max), 
        the interval from [max, min] is searched (since max >= min)
 */
std::vector<File*> FileAVL::query(size_t min, size_t max) {
    std::vector<File*> result;

    // Your code here.
    if (min >= max) {
        queryRecursive(max, min, result, this->root_);
    }
    else {
        queryRecursive(min, max, result, this->root_);
    }

    return result;
}
