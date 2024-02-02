#include <iostream>
#include <vector>
#include <numeric>
#include <Rmath.h>

std::vector<double> meanKRS_C(std::vector<double> y, std::vector<double> x, std::vector<double> x0, double lambda )
{
    int n = x.size();
    int n0 = x0.size();

    std::vector<double> out;

    for (int i = 0; i < n0; i++)
    {
        std::vector<double> dens_norm = dnorm(x, x0[i], lambda);

        // Calculate the product of dnorm and y
        std::vector<double> dens_norm_y;
        for (int j = 0; j < dens_norm.size(); j++)
        {
            dens_norm_y.push_back(dens_norm[j] * y[j]);
        }
        
        double sum_dens_norm_y = std::accumulate(dens_norm_y.begin(), dens_norm_y.end(), 0.0);
        double sum_dens_norm = std::accumulate(dens_norm.begin(), dens_norm.end(), 0.0);
        double element = sum_dens_norm_y / sum_dens_norm;
        out.push_back(element);
    }
    
    return out;
}

// Function to print out the vector
void print_vec(std::vector<double> v) {
    
    for(auto e : v) {
        std::cout << e << " ";
    }

    std::cout << std::endl;
}

// Test out the meanKRS_C function
int main() {
    int nobs = 50;
    std::vector<double> x = runif(nobs);
    std::vector<double> y;
    for (int i = 0; i < nobs; i++)
    {
        y.push_back(sin(4 * M_PI * std::pow(x[i], 3)) + rnorm(1, 0, 0.2));
    }
    
    std::vector<double> x0;
    for (double i = 0; i <= 1; i += 0.1)
    {
        x0.push_back(i);
    }
    

    std::vector<double> krs_result = meanKRS_C(y, x, x0, 0.06);
    print_vec(krs_result);

    return 0;
}
