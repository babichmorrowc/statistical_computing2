// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace arma;
#include <armadillo_lm_funcs.h>

// Same function as in armadillo_lm_local.cpp
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

// Perform k-fold cross-validation for H
// [[Rcpp::export(name = "armadillo_cv_H")]]
Rcpp::List armadillo_lm_local_cv(vec& y, mat& x0, mat& X0, mat& x, mat& X, Rcpp::List& H_values, int k_fold) {
  // Get the number of observations
  int nrow = x0.n_rows;
  // Vector of fits
  vec fitted(nrow);
  // Vector to store the mean squared errors for each value of H
  vec mse(H_values.size(), fill::zeros);

  // Split the data into k-folds
  // Calculate the number of observations in each fold
  int fold_size = nrow / k_fold;
  // Create a vector of indices
  uvec indices = regspace<uvec>(0, nrow - 1);
  // Shuffle the indices
  indices = shuffle(indices);

  // Loop over each value of H
  for (int h = 0; h < H_values.size(); ++h) {
    mat H = H_values[h];
    double total_mse = 0.0;

    // Perform k-fold cross-validation
    for (int fold = 0; fold < k_fold; ++fold) {
      // Get the indices for the training and test sets
      uvec test_indices = indices.subvec(fold * fold_size, (fold + 1) * fold_size - 1);
      uvec train_indices = indices.elem(find(indices < fold * fold_size || indices >= (fold + 1) * fold_size));

      // Get the training and test data
      mat x0_train = x0.rows(train_indices);
      mat X0_train = X0.rows(train_indices);
      vec y_train = y.elem(train_indices);
      mat x0_test = x0.rows(test_indices);
      mat X0_test = X0.rows(test_indices);
      vec y_test = y.elem(test_indices);

      // Fit the model using the training data
      vec y_test_pred = armadillo_lm_local(y_train, x0_test, X0_test, x0_train, X0_train, H);
      
      // Calculate the mean squared error
      double fold_mse = mean(square(y_test - y_test_pred));
      total_mse += fold_mse;
  }

    // Calculate the average mean squared error across the k-folds
    mse(h) = total_mse / k_fold;
  }

  // Find the index of the minimum MSE
  int min_mse_idx = mse.index_min();
  // Choose the corresponding H value
  mat best_H = H_values[min_mse_idx];

  // Refit the model using the chosen H and the entire dataset
  fitted = armadillo_lm_local(y, x0, X0, x, X, best_H);

  // Return a list of the selected H and the fitted values
  return Rcpp::List::create(Rcpp::Named("H") = best_H,
                            Rcpp::Named("fitted") = fitted);
}

