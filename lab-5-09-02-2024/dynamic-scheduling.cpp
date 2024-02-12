#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define rep                               \
    for (long i = 0; i < 1000000000; i++) \
    {                                     \
    }

#define NUM_THREADS 4

int N = 1000 ; 

int main()
{
        int a[N][N] = {0};
        int j;

        int tid_to_comp[NUM_THREADS] = {0} ; 

    #pragma omp parallel shared(a, N) private(j) num_threads(NUM_THREADS)
        {
    #pragma omp for schedule(dynamic)
            for (int i = 0; i < N; i++)
        {
            for (int j = i; j < N; j++){
                a[i][j] = rand();
                tid_to_comp[omp_get_thread_num()]++; 
            }
        }
    }

    for(int x: tid_to_comp)
        cout << x << ' '; 
    cout<<endl;

    return 0;
}
