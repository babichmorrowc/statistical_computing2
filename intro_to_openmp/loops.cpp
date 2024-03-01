#include <iostream>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        int nloops = 0; // Each thread will have its own copy of nloops

        #pragma omp for // This pragma will distribute the loop iterations among the threads
        for (int i=0; i<1000; ++i)
        {
            ++nloops;
        }

        int thread_id = omp_get_thread_num(); // Get the thread number

        std::cout << "Thread " << thread_id << " performed "
                  << nloops << " iterations of the loop.\n";
    }

    return 0;
}