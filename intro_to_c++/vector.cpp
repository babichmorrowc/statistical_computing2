#include <iostream>
#include <vector>

void print_int_vec(std::vector<int> v) {
    
    /*
    // first type of for loop
    for(int i=0; i<v.size(); i++) {
        std::cout << v[i] << " ";
    }
    */

    // second type of for loop in C++
    for(auto e : v) {
        std::cout << e << " ";
    }

    std::cout << std::endl;
}

int main() {
    /*
    std::vector<int> v; // similar to declaring int a, except by default it's an empty vector
    v.push_back(4);
    v.push_back(2);
    */
    std::vector<int> v = {4, 2, 9, 12, 13};
    
    print_int_vec(v);

    return 0;
}