#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 4
#define NUM_ELEMENTS 1024 * 65536

int main()
{

    vector<int> v(NUM_ELEMENTS);
    // fill array with distinct random values
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        v[i] = rand() % 1000000 - rand() % 1000000;
    }

    int x;
    cin >> x;

    vector<int> ans(2 * NUM_ELEMENTS);
#pragma omp parallel for num_threads(NUM_THREADS)
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        ans[i + NUM_ELEMENTS] = v[i] >= x ? 0 : 1;
    }

    int steps = int(log2(NUM_ELEMENTS)) + 1;
    for (int i = 1; i <= steps; i++)
    {
        int total_threads = (long long)(NUM_ELEMENTS / (pow(2, i)));
        int offset = NUM_ELEMENTS / pow(2, i);
        int s = offset, e = offset + total_threads;
#pragma omp parallel for num_threads(NUM_THREADS) shared(offset, s, e)
        for (int i = s; i < e; i++)
        {
            ans[i] = ans[2 * i] + ans[2 * i + 1];
        }
    }

    cout << "rank of element is " << ans[1]+1 << endl;
    return 0;
}
