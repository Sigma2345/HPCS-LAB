#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define rep                               \
    for (long i = 0; i < 1000000000; i++) \
    {                                     \
    }
#define N 1024 * 65536
#define NUM_THREADS 4

int main()
{

    vector<long long> v(N);
    for (int i = 0; i < N; i++)
    {
        // v[i] = rand() % N;
        v[i] = 1;
    }
    // for (int x : v)
    //     cout << x << ' ';
    // cout << endl;
    vector<long long> ans(2 * N, -1);
    for (int i = N - 1; i >= 0; i--)
    {
        ans[i + N] = v[i];
    }

    // 16 -> 8 -> 4 -> 2 -> 1

    int steps = int(log2(N)) + 1;
    for (int i = 1; i <= steps; i++)
    {
        int total_threads = (long long)(N / (pow(2, i)));
        int offset = N / pow(2, i);
        // cout << "N IS " << N << " AND STEPS IS " << steps << endl;
        // cout << "OFFSET IS " << offset << endl;
        // cout << total_threads << endl;
        int s = offset, e = offset + total_threads;
#pragma omp parallel for num_threads(NUM_THREADS) shared(offset, s, e) 
        for (int i = s; i < e; i++){
            ans[i] = ans[2 * i] + ans[2 * i + 1]; 
        }
    }
    cout << ans[1] << endl;

    return 0;
}
