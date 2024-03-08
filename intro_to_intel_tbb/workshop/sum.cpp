#include <iostream>

int sum(int x, int y)
{
    return x + y;
}

int main()
{
   // int result = sum(3, 7); // could use auto here
    auto a = sum;
    auto result = a(3, 7);
    std::cout << result << std::endl;
    return 0;
}
