

#include <iostream>

int main()
{
    int n = 45.8;

    if (n < 0)
    {
        std::cout << n << " is negative." << std::endl;
    }
    else if (n > 100)
    {
        std::cout << n << " is large and positive." << std::endl;
    }
    else if (n == 10)
    {
        for (int i=10; i>0; i-=1)
        {
            std::cout << i << "..." << std::endl;
        }
        std::cout << "Blast off!" << std::endl;
    }
    else if (n == 42)
    {
        std::cout << "The answer to life, the universe and everything!" << std::endl;
    }
    else
    {
        std::cout << "What is " << n << "?" << std::endl;
    }

    return 0;
}

/*
int main()
{
    std::cout << "Loop 1" << std::endl;
    for (int i=0; i<10; ++i)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Loop 2" << std::endl;
    for (int i=500; i>0; i -= 100)
    {
        std::cout << i << std::endl;
    }

    std::cout << "Loop 3" << std::endl;
    for (int puppy=30; puppy<=100; puppy += 5)
    {
        std::cout << puppy << std::endl;
    }

    std::cout << "Loop 4" << std::endl;
    for (int i=1; i<=3; ++i)
    {
        for (int j=1; j<=3; ++j)
        {
            std::cout << (i*j) << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}
*/

