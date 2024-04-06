#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 4
#define NUM_ELEMENTS 1000000

int main()
{

    vector<int> v(NUM_ELEMENTS, 1);
    int sum = 0;
    clock_t begin = clock();

#pragma omp parallel for num_threads(NUM_THREADS) schedule(dynamic) reduction(+ : sum)
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        sum += v[i];
    }
    clock_t end = clock();

    cout << (end - begin) << endl;
    cout << sum << endl;

    return 0;
}
