#include <iostream>
#include <vector>
#include "include/part1.h"

using namespace part1;

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

int main()
{
  auto a = std::vector<int>( { 1, 2, 3, 4, 5 } );
  auto b = std::vector<int>( { 6, 7, 8, 9, 10 } );
  
  auto result = map( sum, a, b );
  print_vector(result);
  
  result = map( difference, a, b );
  print_vector(result);
  
  result = map( multiply, a, b );
  print_vector(result);
  
  return 0;
}