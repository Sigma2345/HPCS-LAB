#include <bits/stdc++.h>
#include <omp.h>
using namespace std; 
#define NUM_THREADS 4
#define NUM_ELEMENTS 4096

int main(){

    // freopen("file_seq.txt", "w", stdout); 
    vector<int> v(NUM_ELEMENTS);
    // fill array with distinct random values
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        v[i] = rand() % 100 + 1;
    }

    // for(int x: v) cout<<x<<' ' ; 
    // cout<<endl ; 

    int indx; 
    cin>>indx ; 

    vector<int> soln(NUM_ELEMENTS); 
    int nums_less_than_equal = 0;
    for(int x: v) if(x <= v[indx]) nums_less_than_equal++ ; 
    // cout<<nums_less_than_equal<<endl ;
    soln[nums_less_than_equal-1] = v[indx]; 
    int i = 0, j = nums_less_than_equal ; 
    // cout<<i << ' '<<j<<endl ; 
    for(int it = 0  ; it<v.size() ; it++){
        if(it==indx) continue; 
        else{
            if(v[it] <= v[indx]) soln[i++] = v[it]; 
            else soln[j++] = v[it];   
        }
    }

    for(int x: soln) cout<<x<<' ' ; 
    cout<<endl ;

    return 0; 
}