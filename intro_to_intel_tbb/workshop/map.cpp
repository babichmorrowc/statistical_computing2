#include <iostream>
#include <vector>


template<class FUNC, class T>
auto map(FUNC func, const std::vector<T> &arg1, const std::vector<T> &arg2)
{
  int nvalues = std::min( arg1.size(), arg2.size() );
  
  auto result = std::vector<T>(nvalues);
  
  for (int i=0; i<nvalues; ++i)
  {
    result[i] = func(arg1[i], arg2[i]);
  }
  
  return result;
}

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

template<class T>
void print_vector(const std::vector<T> &values)
  // const: function doesn't change the vector
  // & is reference: function doesn't make a copy of the vector, but uses the original
{
  std::cout << "[";
  
  for (const T &value : values)
  {
    std::cout << " " << value;
  }
  
  std::cout << " ]" << std::endl;
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