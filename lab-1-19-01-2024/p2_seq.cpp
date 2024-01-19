#include <bits/stdc++.h>
#include <pthread.h>
using namespace std;
#define N_ARR 10

int arr1[N_ARR];

int main()
{
    for (int i = 0; i < N_ARR; i++){
        arr1[i] = i+1;  
    }
        int sum = 0;  
    for (int i = 0; i < N_ARR; i++)
    {
        sum += arr1[i]; 
    }

    return 0;
}
