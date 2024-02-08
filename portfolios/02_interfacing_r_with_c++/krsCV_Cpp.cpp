#include <random>
#include <algorithm>
#include <iostream>
#include <vector>
extern "C" {
  #include <R.h>
  #include <Rinternals.h>
  #include <Rmath.h>
}

// Use extern "C" to prevent C++ name mangling
extern "C" {
  SEXP krsCV_Cpp(SEXP y_vec, SEXP x_vec, SEXP k_val, SEXP lambda_sequence);
  std::vector<double> meanKRS(std::vector<double> y_vec,
                              std::vector<double> x_vec,
                              std::vector<double> x0_vec,
                              double lambda_param);
}

// Function to perform kernel regression smoothing
// Takes C++ vectors as input and returns a C++ vector
std::vector<double> meanKRS(std::vector<double> y_vec,
                            std::vector<double> x_vec,
                            std::vector<double> x0_vec,
                            double lambda_param)
{
  
  int n = x_vec.size();
  int n0 = x0_vec.size();
  std::vector<double> out(n0);
  
  // Calculate the sum of the results of dnorm
  for (int i = 0; i < n0; i++)
  {
    double sum_dens_norm_y = 0;
    double sum_dens_norm = 0;
    
    for (int j = 0; j < n; j++)
    {
      double dens_norm = dnorm(x_vec[j], x0_vec[i], lambda_param, 0);
      sum_dens_norm_y += dens_norm * y_vec[j];
      sum_dens_norm += dens_norm;
    }
    
    out[i] = sum_dens_norm_y / sum_dens_norm;
  }
  
  return out;
}

// Function to perform k-fold cross-validation for kernel regression smoothing
// Takes R objects as input and returns a R vector
SEXP krsCV_Cpp(SEXP y_vec, SEXP x_vec, SEXP k_val, SEXP lambda_sequence)
{
  int n = length(x_vec);
  int lambda_length = length(lambda_sequence);
  int k = INTEGER(k_val)[0];
  SEXP out;
  PROTECT(out = allocVector(REALSXP, 1));
  
  double *x = REAL(coerceVector(x_vec, REALSXP));
  double *y = REAL(coerceVector(y_vec, REALSXP));
  
  // Create a sequence from 1 to k and repeat it to length n
  std::vector<int> sequence(n);
  for (int i = 0; i < n; ++i) {
    sequence[i] = (i % 5) + 1;
  }
  // Shuffle the sequence
  std::random_shuffle(sequence.begin(), sequence.end());
  
  std::vector<double> mse_lambdas(lambda_length);
  
  // Loop over the values of lambda
  for (int l = 0; l < lambda_length; l++) {
    double lambda_l = REAL(lambda_sequence)[l];
    std::vector<double> mse_vec_l(k);
    // Loop over the k folds
    for (int i = 0; i < k; i++) {
      // Set up training and testing sets
      std::vector<double> x_train;
      std::vector<double> x_test;
      std::vector<double> y_train;
      std::vector<double> y_test;
      for (int j = 0; j < n; j++) {
        if (sequence[j] == i + 1) {
          x_train.push_back(x[j]);
          y_train.push_back(y[j]);
        } else {
          x_test.push_back(x[j]);
          y_test.push_back(y[j]);
        }
      }
      
      // Fit the model on the training set and get values for x_test
      std::vector<double> mu_pred = meanKRS(y_train, x_train, x_test, lambda_l);
      
      // Calculate the mean squared error for the kth fold
      double mse = 0;
      for (int j = 0; j < x_test.size(); j++) {
        mse += pow(y_test[j] - mu_pred[j], 2);
      }
      mse /= x_test.size();
      // Add it to mse_vec_l
      mse_vec_l[i] = mse;
    }
    
    // Calculate the mean of the mean squared errors for lambda value lambda_l
    double mean_mse = 0;
    for (int j = 0; j < k; j++) {
      mean_mse += mse_vec_l[j];
    }
    mean_mse /= k;
    mse_lambdas[l] = mean_mse;
  }
  
  // Find the lambda value that minimizes the mean squared error
  double min_mse = mse_lambdas[0];
  int min_mse_index = 0;
  for (int i = 1; i < lambda_length; i++) {
    if (mse_lambdas[i] < min_mse) {
      min_mse = mse_lambdas[i];
      min_mse_index = i;
    }
  }
  
  // Create the output
  REAL(out)[0] = REAL(lambda_sequence)[min_mse_index];
  UNPROTECT(1);
  
  return out;
}