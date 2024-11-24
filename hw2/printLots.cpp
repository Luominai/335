#include <iostream>
#include <list>

void printLots(const std::list<int>& L, const std::list<int>& P) {
    auto position = P.begin();
    int currentIndex = 0;

    for (auto list = L.begin(); list != L.end(); ++list) {
        if (currentIndex == *position) {
            std::cout << *list << std::endl;
            ++position;
        }
        currentIndex++;
    }
}

template <typename Iterator, typename Object>
Iterator find( Iterator start, Iterator end, const Object & x ) {
    while(start != end) {
        if (*start == x) {
            return start;
        } 
        start++;
    }
    return start;
}

int main() {
    std::list<int> L = {0,1,2,3,4,5};
    std::list<int> P = {1,3,5};
    printLots(L, P);
    std::cout << *(find(L.begin(), L.end(), 3));
}