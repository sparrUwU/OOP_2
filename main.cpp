#include "twelve.hpp"
#include <iostream>

int main(){
    try {
        Twelve a = {'0', '0', '1'};
        std::cout << a.toString() << std::endl;
        
        Twelve b = {'A', '0', '2'};
        std::cout << a.add(b).toString() << std::endl;
        
        std::cout << (a.equals(b) ? "true" : "false") << std::endl;
        std::cout << (!a.equals(b) ? "true" : "false") << std::endl;
        std::cout << (a.greaterThan(b) ? "true" : "false") << std::endl;
        
        std::cout << a.subtract(b).toString() << std::endl;
        
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return 0;
}