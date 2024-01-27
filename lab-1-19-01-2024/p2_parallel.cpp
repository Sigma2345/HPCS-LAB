#include <bits/stdc++.h>
#include <pthread.h>
#include <mutex>
using namespace std;
 
#define N_ARR 10
#define N_THREADS 4

mutex m; 

int arr1[N_ARR];
int final_sum = 0;  

struct thread_info {
    int s; 
    int e;
    int thread_num; 
};

void *f(void *arg){
    thread_info t = *(thread_info*) arg ;

    int local = 0;
    if(t.s >= N_ARR){
        printf("No need sum compute thread %d\n", t.thread_num);
        return NULL; 
    }
    for (int i = t.s; i <= t.e; i++)
    {
        local += arr1[i]; 
    }

    // mutex
    m.lock();
    final_sum += local;
    m.unlock(); 

    printf("Done thread %d between %d and %d\n", t.thread_num, t.s, t.e);
}

int main()
{
    for (int i = 0; i < N_ARR;  i++) arr1[i] = i+1;
    pthread_t th[N_THREADS];

    thread_info thread_data_arr[N_THREADS];
    int s = 0;
    int size = N_ARR / N_THREADS; 
    for (int i = 0; i < N_THREADS && s < N_ARR; i++)
    {
        thread_data_arr[i].s = s;
        thread_data_arr[i].e = s + size;
        if(thread_data_arr[i].e >= N_ARR){
            thread_data_arr[i].e = N_ARR-1;  
        }
        thread_data_arr[i].thread_num = i ;

        s = thread_data_arr[i].e + 1; 
    }

    for (int i = 0; i < N_THREADS; i++){
        if(pthread_create(&th[i], NULL, &f, &thread_data_arr[i])){
            printf("Couldn't start thread %d", i); 
        }
    }

    for (int i = 0; i < N_THREADS; i++){
        if(pthread_join(th[i], NULL)){
            printf("couldn't merge thread %d", i); 
        }
    }
    cout << final_sum << endl; 

    return 0;
}
