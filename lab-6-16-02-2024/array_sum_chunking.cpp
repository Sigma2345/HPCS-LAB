#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 4
#define NUM_ELEMENTS 1000000

int main()
{

    vector<int> v(NUM_ELEMENTS, 1);
    vector<int> sum(NUM_THREADS, 0);
    clock_t begin = clock();
#pragma omp parallel for num_threads(NUM_THREADS) schedule(dynamic)
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        sum[omp_get_thread_num()] += v[i];
    }
    clock_t end = clock();
    cout << (end - begin) << endl;
    int ans = 0;
    for(int x: sum)
        ans += x;

    cout << ans << endl;

    return 0;
}
