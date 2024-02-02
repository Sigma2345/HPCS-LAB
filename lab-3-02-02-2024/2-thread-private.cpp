#include <iostream>
#include <omp.h>
#include <stdio.h>
using namespace std;
#define rep                        \
    for (long i = 0; i < 1e9; i++) \
    {                              \
    }

void f(int &tid)
{
    // cout << "hello from thread " << tid << endl;
    cout << "hello from thread " << tid << " at address " << &tid << endl;
}

int tid;
#pragma omp threadprivate(tid)
int main()
{

    int numt;

#pragma omp parallel default(shared) num_threads(7)
    {
        // rep
        tid = omp_get_thread_num();
        if (tid <= 2)
        {
#pragma omp for nowait
            for (long long i = 0; i < 1000000000; i++){}
            // usleep(10); 
            numt = omp_get_num_threads();
        }
#pragma omp critical
        cout << "hello from thread " << tid << " at address " << &tid << endl;
    }
    cout << "-----------------------------------------" << endl;

// if here total threads created less than above threads then
// threads are closed
// if here total threads created more than above threads then
// threads persist
#pragma omp parallel default(shared) num_threads(8)
    {
#pragma omp critical
        f(tid);
    }
    cout << "-----------------------------------------" << endl;
#pragma omp parallel default(shared) num_threads(7)
    {
#pragma omp critical
        f(tid);
    }
    return 0;
}
