// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace arma;

// Linear model using QR decomposition
vec armadillo_lm(mat& X, vec& y) {
  mat Q;
  mat R;
  
  qr_econ(Q, R, X);
  vec beta = solve(R, (trans(Q) * y));
  return beta;
}

// Function for evaluating multivariate Gaussian density
// L is the lower triangular factor of the Cholesky decomp of the covariance
vec dmvnInt(mat& X, const rowvec& mu, mat& L)
{
  unsigned int d = X.n_cols;
  unsigned int m = X.n_rows;
  
  vec D = L.diag();
  // Define vector that will contain the density values
  vec out(m);
  vec z(d);
  
  double acc;
  unsigned int icol, irow, ii;
  for(icol = 0; icol < m; icol++) // Loop over the x values
  {
    for(irow = 0; irow < d; irow++)
    {
      acc = 0.0;
      for(ii = 0; ii < irow; ii++) acc += z.at(ii) * L.at(irow, ii);
      // z_i = L^-1 (x_i - mu)
      z.at(irow) = ( X.at(icol, irow) - mu.at(irow) - acc ) / D.at(irow);
    }
    out.at(icol) = sum(square(z));
  }
  
  out = exp( - 0.5 * out - ( (d / 2.0) * log(2.0 * M_PI) + sum(log(D)) ) );
  
  return out;
}

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