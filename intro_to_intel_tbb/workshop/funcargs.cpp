#include <iostream>

int sum(int x, int y)
{
    return x + y;
}

int difference(int x, int y)
{
     return x - y;
}

int multiply(int x, int y)
{
     return x * y;
}

template<class FUNC, class ARG1, class ARG2>
auto call_function(FUNC func, ARG1 arg1, ARG2 arg2)
{
    std::cout << "Calling a function with arguments " << arg1
              << " and " << arg2;

    auto result = func(arg1,arg2);

    std::cout << ". The result is " << result << std::endl; 

    return result;
}

int main()
{
    auto result = call_function( difference, 9, 2 );
    std::cout << result << std::endl;

    result = call_function( sum, 3, 7 );
    std::cout << result << std::endl;

    result = call_function( multiply, 4, 5 );
    std::cout << result << std::endl;

    return 0;
}
