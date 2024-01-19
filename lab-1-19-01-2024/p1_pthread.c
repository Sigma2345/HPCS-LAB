#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define N_ARR 10000000
#define N_THREADS 4

int arr1[N_ARR], arr2[N_ARR], arr3[N_ARR];

void *addfunc(void *t)
{

    int i = *(int *)t;

    // printf("addition starting at %d\n", i);
    // 1 2 3 4 5 6 7 8
    // 1 2 3 4 5 6 7 8
    for (int index = i; index < N_ARR; index += N_THREADS)
    {
        arr3[index] = arr2[index] + arr1[index];
    }
}

int main()
{

    for (int i = 1; i <= N_ARR; i++)
    {
        arr1[i - 1] = i;
        arr2[i - 1] = 2 * i;
    }
    
    // printf("arr1[i]: ");
    // for (int i = 0; i < N_ARR; i++)
    // {
    //     printf("%d ", arr1[i]);
    // }
    // printf("\n");

    // printf("arr2[i]: ");
    // for (int i = 0; i < N_ARR; i++)
    // {
    //     printf("%d ", arr2[i]);
    // }
    // printf("\n");

    pthread_t th[N_THREADS];
    int x[N_THREADS];  
    for(int i = 0;  i<N_THREADS;  i++){
        x[i] = i; 
    }
    // printf("nhjbsk"); 
    for (int i = 0; i < N_THREADS; i++)
    {
        // printf("Created thread %d", i);
        if (pthread_create(&th[i], NULL, &addfunc, (void *)&x[i]))
        {
            printf("Couldn't start thread");
            exit(1);
        } 
    }
    // printf("nhjbsk");

    for (int i = 0; i < N_THREADS; i++)
    {
        if (pthread_join(th[i], NULL))
        {
            printf("Couldn't merge thread");
            exit(1);
        }
    }

    // printf("arr3[i]: ");
    // for (int i = 0; i < N_ARR; i++)
    // {
    //     printf("%d ", arr3[i]);
    // }
    // printf("\n");

    return 0;
}
