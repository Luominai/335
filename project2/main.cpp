#include "FileAVL.hpp"
#include "FileTrie.hpp"

bool testQuery(FileAVL* tree, const int &min, const int &max, const std::vector<File*> &expected) {
    std::vector<File*> result = tree->query(min, max); 

    std::cout << std::endl;
    std::cout << "result: ";
    for (File* file : result) {
        std::cout << file->getName() << " ";
    }

    std::cout << std::endl;
    std::cout << "expect: ";
    for (File* file : expected) {
        std::cout << file->getName() << " ";
    }

    std::cout << std::endl;
    return result == expected;
}

int main() {
    File* f1 = new File("a.txt", "1");
    File* f2 = new File("ab.txt", "12");
    File* f3 = new File("abc.txt", "123");
    File* f4 = new File("bc.txt", "1234");
    File* f5 = new File("bcd.txt", "12345");
    File* f6 = new File("AbCd.txt", "123456");
    File* f7 = new File("B.txt", "1234567");

    std::vector<File*> allFiles = {f1,f2,f3,f4,f5,f6,f7};
    std::vector<File*> expected;
    FileAVL* tree = new FileAVL();

    for (File* file : allFiles) { 
        tree->insert(file); 
    }

    std::cout << "query tests" << std::endl;
    // test query
    expected = {f2,f3,f4};
    if (testQuery(tree, 2, 4, expected)) {
        std::cout << "passed test 1" << std::endl;
    }
    else {
        std::cout << "failed test 1" << std::endl;
    }

    // test min max reversal
    expected = {f2,f3,f4};
    if (testQuery(tree, 4, 2, expected)) {
        std::cout << "passed test 2" << std::endl;
    }
    else {
        std::cout << "failed test 2" << std::endl;
    }

    // test high min
    expected = {};
    if (testQuery(tree, 10, 100, expected)) {
        std::cout << "passed test 3" << std::endl;
    }
    else {
        std::cout << "failed test 3" << std::endl;
    }

    // test high max
    expected = allFiles;
    if (testQuery(tree, 0, 100, expected)) {
        std::cout << "passed test 4" << std::endl;
    }
    else {
        std::cout << "failed test 4" << std::endl;
    }

    // test min == max
    expected = {f2};
    if (testQuery(tree, 2, 2, expected)) {
        std::cout << "passed test 5" << std::endl;
    }
    else {
        std::cout << "failed test 5" << std::endl;
    }

    // test null tree
    expected = {};
    FileAVL* nullTree = new FileAVL();
    if (testQuery(nullTree, 1, 5, expected)) {
        std::cout << "passed test 6" << std::endl;
    }
    else {
        std::cout << "failed test 6" << std::endl;
    }

    
    FileTrie* trie = new FileTrie();
    for (File* file : allFiles) {
        trie->addFile(file);
    }

    std::cout << "testing trie" << std::endl;
    std::unordered_set<File*> set;

    // full trie print
    set = trie->getFilesWithPrefix("");
    std::cout << "head: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;

    set = trie->getFilesWithPrefix("a");
    std::cout << "a: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;
    set = trie->getFilesWithPrefix("b");
    std::cout << "b: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;

    set = trie->getFilesWithPrefix("ab");
    std::cout << "ab: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;
    set = trie->getFilesWithPrefix("bc");
    std::cout << "bc: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;

    set = trie->getFilesWithPrefix("abc");
    std::cout << "abc: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;
    set = trie->getFilesWithPrefix("bcd");
    std::cout << "bcd: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;
    
    std::cout << "prefix not found" << std::endl;
    set = trie->getFilesWithPrefix("z");
    std::cout << "z: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;

    std::cout << "capitalized prefix" << std::endl;
    set = trie->getFilesWithPrefix("AB");
    std::cout << "AB: ";
    for(auto it = set.begin(); it != set.end(); ++it) {
        std::cout << (*it)->getName() << "  ";
    }
    std::cout << std::endl;
}