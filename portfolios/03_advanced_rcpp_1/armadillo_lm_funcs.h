// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace arma;

// Linear model using QR decomposition
vec armadillo_lm(mat& X, vec& y) {
  mat Q;
  mat R;
  
  qr_econ(Q, R, X); // QR decomposition of X
  vec beta = solve(R, (trans(Q) * y)); // Solve the system R * beta = Q^T * y for beta
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
    for(irow = 0; irow < d; irow++) // Loop over the dimensions
    {
      acc = 0.0;
      for(ii = 0; ii < irow; ii++) acc += z.at(ii) * L.at(irow, ii);
      z.at(irow) = ( X.at(icol, irow) - mu.at(irow) - acc ) / D.at(irow);
    }
    out.at(icol) = sum(square(z));
  }
  
  // Compute the density
  out = exp( - 0.5 * out - ( (d / 2.0) * log(2.0 * M_PI) + sum(log(D)) ) );
  
  return out;
}