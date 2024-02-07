#include <random>
#include <algorithm>
#include <iostream>

std::vector<int> krsCV_C(std::vector<int> y_vec, std::vector<int> x_vec, int k_val, std::vector<int> lambda_sequence)
{
  
  int n = x_vec.size();
  
  // Create a sequence from 1 to k and repeat it to length n
  std::vector<int> out(n);
  for (int i = 0; i < n; ++i) {
    out[i] = (i % k_val) + 1;
  }

  std::random_shuffle(out.begin(), out.end());
  
  return out;
}

void print_int_vec(std::vector<int> v) {
    
    for(auto e : v) {
        std::cout << e << " ";
    }

    std::cout << std::endl;
}


int main() {
    std::vector<int> y = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 5;
    std::vector<int> lambda_sequence = {1, 2, 3, 4, 5};

    std::vector<int> krsCV_result = krsCV_C(y, x, k, lambda_sequence);

    print_int_vec(krsCV_result);

    return 0;
}