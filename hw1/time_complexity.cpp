#include <chrono>
#include <iostream>
#include <functional>

void timeFunction(std::function<void(int& sum, int& n)> func) {
    int sum = 0;
    int n = 200;
    const auto t1 = std::chrono::high_resolution_clock::now();
    func(sum, n);
    const auto t2 = std::chrono::high_resolution_clock::now();
    const auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << int_ms.count() << std::endl;
}

int main() {
    // O(n)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            sum++;
        }
    });
    // O(n^2)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                sum++;
            }
        }
    });
    // O(n^3)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n*n; j++) {
                sum++;
            }
        }
    });
    // O(n^2)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                sum++;
            }
        }
    });
    // O(n^4)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i*i; j++) {
                for(int k = 0; k < j; k++) {
                    sum++;
                }
            }
        }
    });
    // O(n^4)
    timeFunction([](int sum, int n){
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i*i; j++) {
                if (j % i == 0) {
                    for(int k = 0; k < j; k++) {
                        sum++;
                    }
                }
            }
        }
    });
}