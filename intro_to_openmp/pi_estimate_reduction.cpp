#include <random>
#include <cmath>
#include <iostream>
#include <omp.h>

int main() {

    std::random_device rd;
    int pts_inside = 0;
    int pts_outside = 0;

    #pragma omp parallel reduction(+ : pts_inside, pts_outside)
    {
        // Set up random number generator stuff
        std::default_random_engine generator(rd());
        std::uniform_real_distribution random(-1.0, 1.0);

        // Thread number
        // int thread_id = omp_get_thread_num();

        // Counters within each thread
        int thread_pts_inside = 0;
        int thread_pts_outside = 0;

        #pragma omp for
        for (int i = 0; i < 100000000; i++)
        {
            // Generate random x and y coordinates
            double x = random(generator);
            double y = random(generator);
            // Calculate distance from center
            double distance = std::sqrt(x*x + y*y);

            if (distance <= 1.0)
            {
                thread_pts_inside++;
            }
            else
            {
                thread_pts_outside++;
            }
        }

        double thread_pi_estimate = 4.0 * thread_pts_inside / (thread_pts_inside + thread_pts_outside);
        double thread_n_pts = thread_pts_inside + thread_pts_outside;

        pts_inside += thread_pts_inside;
        pts_outside += thread_pts_outside;

        /*
        #pragma omp critical
        {
            std::cout << "Thread " << thread_id << " estimated value of pi: " << thread_pi_estimate << " (includes " << thread_n_pts << " points)" << std::endl;
        }
        */
        
    }

    double pi_estimate = 4.0 * pts_inside / (pts_inside + pts_outside);
    std::cout << "Estimated value of pi: " << pi_estimate << std::endl;

    return 0;
}