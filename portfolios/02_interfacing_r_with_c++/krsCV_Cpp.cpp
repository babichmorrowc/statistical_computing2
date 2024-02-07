#include <random>
#include <algorithm>
#include <iostream>
extern "C" {
  #include <R.h>
  #include <Rinternals.h>
  #include <Rmath.h>
}

// Use extern "C" to prevent C++ name mangling
extern "C" {
  SEXP krsCV_Cpp(SEXP x_vec, SEXP k_val, SEXP lambda_sequence);
}

SEXP krsCV_Cpp(SEXP x_vec, SEXP k_val, SEXP lambda_sequence)
{
  int n;
  int lambda_length;
  int k;
  SEXP out;
  
  n = length(x_vec);
  lambda_length = length(lambda_sequence);
  k = INTEGER(k_val)[0];
  
  double *x = REAL(coerceVector(x_vec, REALSXP));
  
  out = PROTECT(allocVector(INTSXP, n));
  
  // Create a sequence from 1 to k and repeat it to length n
  std::vector<int> sequence(n);
  for (int i = 0; i < n; ++i) {
    sequence[i] = (i % k) + 1;
  }
  // Shuffle the sequence
  std::random_shuffle(sequence.begin(), sequence.end());
  
  for (int l = 0; l < lambda_length; l++) {
    for (int i = 0; i < k; i++) {
      // Set up training and testing sets
      std::vector<double> x_train;
      std::vector<double> x_test;
      
    }
  }
  
  UNPROTECT(1)
  return out;
}