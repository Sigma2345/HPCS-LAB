#include<bits/stdc++.h>
#include<omp.h>
using namespace std; 
#define NUM_THREADS 10
#define NUM_ELEMENTS 1024

int main(){

    int arr[NUM_ELEMENTS], arr2[2*NUM_ELEMENTS]; 
#pragma omp parallel for num_threads(NUM_THREADS)
    for(int i = 0 ; i<NUM_ELEMENTS ; i++){
        arr[i] = arr2[i+NUM_ELEMENTS] = 1 ;
    }

#pragma omp parallel num_threads(NUM_THREADS) 
{
    #pragma omp single
    {
        // for(int i = NUM_ELEMENTS; i<2*NUM_ELEMENTS; i++){
        //     #pragma task depend(out: arr2[i])
        //     {
        //         printf("Creating task for index: %d\n", i); 
        //     }
        // }
        for(int i = NUM_ELEMENTS -1 ; i>0 ; i--){
           
           if(i<NUM_ELEMENTS/2){
            #pragma omp task depend(in: arr2[2*i+1], arr2[2*i]) depend(out: arr2[i])
                {
                    arr2[i] = arr2[2*i+1] + arr2[2*i] ; 
                    printf("i: %d\narr2[i]: %d\nthread_id: %d\n----------------------------\n", i, arr[i], omp_get_thread_num()); 
                }
           }
           else{
            #pragma omp task depend (out: arr2[i])
                {
                    for(int j = 0 ; j<1000000000 ; j++); 
                    arr2[i] = arr2[2*i+1] + arr2[2*i] ;
                }
           }
        }
    }
} 



    for(int x: arr2){
        cout<<x<<' ' ; 
    }
    cout<<endl ; 

    cout<<arr2[1]<<endl ; 


    return 0; 
}