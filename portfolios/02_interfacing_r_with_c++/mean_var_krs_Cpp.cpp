#include <vector>
#include <cmath>
extern "C" {
  #include <R.h>
  #include <Rinternals.h>
  #include <Rmath.h>
}

// Use extern "C" to prevent C++ name mangling
extern "C" {
  SEXP mean_var_krs_Cpp(SEXP y_vec, SEXP x_vec, SEXP x0_vec, SEXP lambda_param);
}

SEXP mean_var_krs_Cpp(SEXP y_vec, SEXP x_vec, SEXP x0_vec, SEXP lambda_param) {
  
  int n = length(x_vec);
  int n0 = length(x0_vec);
  
  double *y = REAL(coerceVector(y_vec, REALSXP));
  double *x = REAL(coerceVector(x_vec, REALSXP));
  double *x0 = REAL(coerceVector(x0_vec, REALSXP));
  double lambda = REAL(lambda_param)[0];
  
  std::vector<double> mu(n);
  
  for (int i = 0; i < n; i++) {
    double sum_dens_norm_y = 0;
    double sum_dens_norm = 0;
    
    for (int j = 0; j < n; j++) {
      double dens_norm = dnorm(x[j], x[i], lambda, 0);
      sum_dens_norm_y += dens_norm * y[j];
      sum_dens_norm += dens_norm;
    }
    
    mu[i] = sum_dens_norm_y / sum_dens_norm;
  }
  
  
  std::vector<double> resAbs(n);
  for (int i = 0; i < n; i++) {
    resAbs[i] = std::abs(y[i] - mu[i]);
  }
  
  std::vector<double> madHat(n0);
  
  for (int i = 0; i < n0; i++) {
    double sum_dens_norm_resAbs = 0;
    double sum_dens_norm = 0;
    
    for (int j = 0; j < n; j++) {
      double dens_norm_resAbs = dnorm(x[j], x0[i], lambda, 0);
      sum_dens_norm_resAbs += dens_norm_resAbs * resAbs[j];
      sum_dens_norm += dens_norm_resAbs;
    }
    
    madHat[i] = sum_dens_norm_resAbs / sum_dens_norm;
  }
  
  std::vector<double> w(n0);
  for (int i = 0; i < n0; i++) {
    w[i] = 1 / madHat[i];
  }
  double mean_w = 0;
  for (int i = 0; i < n0; i++) {
    mean_w += w[i];
  }
  mean_w = mean_w / n0;
  for (int i = 0; i < n0; i++) {
    w[i] = w[i] / mean_w;
  }
  
  SEXP out;
  PROTECT(out = allocVector(REALSXP, n0));
  
  for (int ii = 0; ii < n0; ii++) {
    double sum_dens_norm_y = 0;
    double sum_dens_norm = 0;
    
    for (int j = 0; j < n; j++) {
      double dens_norm = dnorm(x[j], x0[ii], lambda * w[ii], 0);
      sum_dens_norm_y += dens_norm * y[j];
      sum_dens_norm += dens_norm;
    }
    
    REAL(out)[ii] = sum_dens_norm_y / sum_dens_norm;
  }
  
  UNPROTECT(1);
  return out;
  
}