#include <iostream> // printing isn't automatically included

int main() { // main executes automatically, always needs to return an integer
    std::cout << "Hello from C++, not Python" << std::endl;

    return 0; // can access this with echo $?
    // don't need to return in main and it will default to returning 0
}