#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
#define NUM_THREADS 4
#define NUM_ELEMENTS 8

int main(){

    vector<int> arr = {6, 4, 16, 10, 16, 14, 2, 8}; 

    int n = arr.size() ;
    vector<int> m(2*n, 0); 

    // phase - 1  
    cout<<"------------------ PHASE 1--------------------"<<endl ;
    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i = 0 ; i<m.size() ; i++){
        m[i+n] = arr[i] ;   
    }

    // phase - 2 
    cout<<"------------------ PHASE 2--------------------"<<endl ;

    int steps = int(log2(arr.size())) + 1;
    cout<<steps<<" steps will be taken"<<endl ;
    cout<<m.size()<<endl ;
    for (int i = 1; i <= steps; i++)
    {
        int total_threads = (long long)(arr.size() / (pow(2, i)));
        int offset = arr.size() / pow(2, i);
        int s = offset, e = offset + total_threads;
        cout<<s<<' '<<e<<endl;
#pragma omp parallel for num_threads(NUM_THREADS) shared(offset, s, e)
        for (int j = s; j < e; j++)
        {
            m[j] = m[2 * j] + m[2 * j + 1];
        }
    }

    cout<<"M: "<<' ' ;
    for(int x: m) cout<<x<<' ' ; 
    cout<<endl ; 

    // phase - 3
    cout<<"------------------ PHASE 3--------------------"<<endl ;
    vector<int> L(n);
    // cout<<"HKHSSN"<<endl ;
    vector<int> R(2*n); 
    R[0] = 0 ;
    // cout<<"HELLO"<<endl ;

    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i=1 ; i<n ; i++){
        L[i] = m[2*i] ; 
    }
    cout<<"L: "<<' ' ; 
    for(int x: L) cout<<x<<' ' ; 
    cout<<endl ;


    // phase - 4
    cout<<"------------------ PHASE 4--------------------"<<endl ;
    steps = int(log2(arr.size()))+1 ;
    cout<<steps<<" steps will be taken"<<endl ;
    // cout<<m.size()<<endl ;
    int e = (long long) 2, s = 1; 
    for (int i = steps; i > 0; i--)
    {
        cout<<s<<' '<<e<<endl;
        #pragma omp parallel for num_threads(NUM_THREADS) shared(e)
        for (int j = s; j < e; j++)
        {
            if(j%2){
                R[j] = R[j/2] + L[j/2] ;
            }
            else {
                R[j] = R[j/2]; 
            }
        }
        e = e*2 ;
        s = s*2 ; 
    }
    cout<<"R: "<<' ' ; 
    for(int x: R) cout<<x<<' ' ; 
    cout<<endl ;


    //phase - 5
    vector<int> B(n, 0); 
    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i =0 ; i<n ; i++){
        B[i] = R[i+n] + m[i+n]; 
    }
    cout<<"B: "<<' ' ; 
    for(int x: B) cout<<x<<' ' ; 
    cout<<endl ;

    return 0 ; 
}
