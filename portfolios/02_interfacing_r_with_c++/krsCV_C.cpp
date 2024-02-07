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
  SEXP krsCV_C(SEXP y_vec, SEXP x_vec, SEXP k_val, SEXP lambda_sequence);
}

SEXP krsCV_C(SEXP y_vec, SEXP x_vec, SEXP k_val, SEXP lambda_sequence)
{
  int n;
  /*double *y;
  double *x;*/
  int k;
  //double *lambda_seq;
  SEXP out;
  
  n = length(x_vec);
  /*y = REAL(coerceVector(y_vec, REALSXP));
  x = REAL(coerceVector(x_vec, REALSXP));*/
  k = INTEGER(k_val)[0];
  /*lambda_seq = REAL(coerceVector(lambda_sequence, REALSXP));*/
  
  out = PROTECT(allocVector(INTSXP, n));
  
  // Create a sequence from 1 to k and repeat it to length n
  for (int i = 0; i < n; ++i) {
    INTEGER(out)[i] = (i % k) + 1;
  }
  
  /*
  std::vector<int> groups(INTEGER(out), INTEGER(out) + n);
  std::copy(sequence.begin(), sequence.end(), groups.begin());
  std::shuffle(groups.begin(), groups.end(), std::default_random_engine(999));
   */
  
  /*
  // Loop over lambda values
  for(double lambda : lambda_seq) {
    // Loop over the folds
    for(int i = 0; i < k; i++) {
      
    }
  }
   */
  
  UNPROTECT(1);
  return out;
}