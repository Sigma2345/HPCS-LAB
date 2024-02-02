#include <bits/stdc++.h>
#include <iostream>
#include <omp.h>
#define NUM_THREADS 4

using namespace std;

int main()
{

    int sz_arr;
    // cin >> sz_arr;
    sz_arr = 1e8;

    vector<long long> a(sz_arr), b(sz_arr), c(sz_arr);

    for (int i = 0; i < sz_arr; i++)
    {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel shared(a, b)
    {
        int thread_id = omp_get_thread_num();
        for (int i = thread_id; i < sz_arr; i += NUM_THREADS)
        {
            // cout << "Executing sum at index " << i << " from thread " << thread_id<<endl ;
            c[i] = a[i] + b[i];
        }
    }

    return 0;
}
