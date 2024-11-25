#include "FileAVL.hpp"
#include "File.hpp"
#include "FileTrie.hpp"

// ALL YOUR CODE SHOULD BE IN THIS FILE. NO MODIFICATIONS SHOULD BE MADE TO FILEAVL / FILE CLASSES
// You are permitted to make helper functions (and most likely will need to)
// You must declare them "inline" | declare & implement them at the top of this file, before query()
// Below query(), implement and document all methods declared in FileTrie.hpp

/**
 * @brief Recursively traverses the FileAVL tree 
 * 
 * @param min The min value of the file size query range.
 * @param max The max value of the file size query range.
 * @param result The vector that is going to store all files found
 * @param current The current node in our traversal
 */
inline void queryRecursive(const size_t &min, const size_t &max, std::vector<File*> &result, Node* const &current) {
    // if the current node is null, return
    if (current == nullptr) {
        return;
    }
    // while the size of the files in the current node are greater than or equal to min, look left
    if (current->size_ >= min) {
        // recurse on left
        queryRecursive(min, max, result, current->left_);
    }
    // if the size of the files here are within our bounds, add them to result
    if (current->size_ >= min && current->size_ <= max) {
        // add all files in this node into result
        for (File* file : current->files_) {
            result.push_back(file);
        }
    }
    // while the size of the files in the current node are less than or equal to max, look right
    if (current->size_ <= max) {
        // recurse on right
        queryRecursive(min, max, result, current->right_);
    }
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

// Default constructor
/**
 * @brief Default Constructor: Construct a new FileTrie object with the head as an empty FileTrieNode
 */
FileTrie::FileTrie() : head {new FileTrieNode()} {}

// Add file, ignore case
 /**
 * @brief Adds a file into the trie
 * @param f The file to be deleted
 */
void FileTrie::addFile(File* f) {
    FileTrieNode* current = this->head;
    // all files get added to the head
    current->matching.insert(f);
    for (char currentChar : f->getName()) {
        // convert the char to lowercase
        char lowercase = char(tolower(currentChar));
        // check if the next node is null
        if (current->next[lowercase] == nullptr) {
            // if it is, create a new node using the lowercase char
            current->next[lowercase] = new FileTrieNode(lowercase);
        }
        // move current
        current = current->next[lowercase];
        // insert file into this node
        current->matching.insert(f);
    }
}

// Search
// Characters allowed are a-z, 0-9, and . (period).
std::unordered_set<File*> FileTrie::getFilesWithPrefix(const std::string& prefix) const {
    FileTrieNode* current = this->head;
    // traverse down the trie and then return matching
    for (char currentChar : prefix) {
        // convert char to lowercase
        char lowercase = char(tolower(currentChar));
        // make sure not to insert new nodes while doing this
        // contains() is c++ 20. If this isn't accepted by gradescope, switch to find()
        if (current->next.find(lowercase) != current->next.end()) {
            current = current->next[lowercase];
        }
        // if we can't go down further, then our prefix doesn't match any files
        else {
            return {};
        }
    }
    return current->matching;
}

// Destructor
FileTrie::~FileTrie() {
    delete head;
}