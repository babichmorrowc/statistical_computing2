#include <iostream>
#include <vector>
#include <numeric>
#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>

SEXP meanKRS_C(SEXP y_vec, SEXP x_vec, SEXP x0_vec, SEXP lambda_param)
{
  
  int n = length(x_vec);
  int n0 = length(x0_vec);
  SEXP out = PROTECT(allocVector(REALSXP, n0));
  
  double y = PROTECT(coerceVector(y_vec, REALSXP));
  double x = PROTECT(coerceVector(x_vec, REALSXP));
  double x0 = PROTECT(coerceVector(x0_vec, REALSXP));
  double lambda = REAL(lambda_param)[0];
  
  for (int i = 0; i < n0; i++)
  {
    double sum_dens_norm_y = 0;
    double sum_dens_norm = 0;
    
    for (int j = 0; j < n; j++)
    {
      double dens_norm = dnorm(x[j], x0[i], lambda);
      sum_dens_norm_y += dens_norm * y[j];
      sum_dens_norm += dens_norm;
    }
    
    out[i] = sum_dens_norm_y / sum_dens_norm;
  }
  
  UNPROTECT(4);
  
  return out;
}