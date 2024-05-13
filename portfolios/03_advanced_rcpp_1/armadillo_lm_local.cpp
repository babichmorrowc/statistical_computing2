// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace arma;
#include <armadillo_lm_funcs.h>

// [[Rcpp::export(name = "armadillo_lm_local")]]
vec armadillo_lm_local( vec& y, mat& x0, mat& X0, mat& x, mat& X, mat& H) {
  
  // Get L for use in dmvnInt
  mat L = chol(H, "lower");
  // Get the number of observations
  int nrow = x0.n_rows;
  // Vector of fits
  vec fitted(nrow);
  // Vector of weights
  vec weights(nrow);
  
  for (int i = 0; i < nrow; i++) {
    // Get the weights
    weights = dmvnInt(x, x0.row(i), L);
    // Get the fitted values
    mat X_weights = X.each_col() % sqrt(weights);
    vec y_weights = y % sqrt(weights);
    vec fit = armadillo_lm(X_weights, y_weights);
    mat X0_fit = X0.row(i) * fit;
    fitted(i) = X0_fit(0);
  }
  
  return fitted;
}