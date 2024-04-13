#include <bits/stdc++.h>
#include <omp.h>
using namespace std; 
#define NUM_THREADS 4
#define NUM_ELEMENTS 8

int R[4*NUM_ELEMENTS]; 
int L[2*NUM_ELEMENTS]; 
int B[2*NUM_ELEMENTS]; 
int ANS[NUM_ELEMENTS]; 

int main(){
    // freopen("file_parallel.txt", "w", stdout); 
    vector<int> v(NUM_ELEMENTS);
    // fill array with distinct random values
    for (int i = 0; i < NUM_ELEMENTS; i++)
    {
        v[i] = rand() % 100 + 1;
    }

    for(int x: v) cout<<x<<' '; 
    cout<<endl ;

    int x;
    cin >> x;

    vector<int> ans(2*NUM_ELEMENTS, 0); 
    ans[NUM_ELEMENTS] = v[x];  

    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i = 0 ; i<NUM_ELEMENTS ; i++){
      if(v[i]<v[x]) ans[i] = v[i]; 
      else if(v[i] > v[x]) ans[NUM_ELEMENTS + i + 1] = v[i] ; 
    }    
    // array compaction
    //characterstic array 
    vector<int> characteristic_array(2*NUM_ELEMENTS, 0); 
    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i  = 0 ; i<ans.size() ;i++){
        characteristic_array[i] = ans[i] != 0 ? 1 : 0 ; 
    }

    for(int x: characteristic_array) cout<<x<<' ' ;
    cout<<endl ; 

    // cout<<"-------------------------- ENTERING PREFIX COMPUTATION ---------------------------"<<endl;
    // vector<int> prefix_sum = prefix_sum_comp(characteristic_array); 
    // for(int x: prefix_sum) cout<<x<<' ' ; 
    // cout<<endl ; 
    vector<int> arr = characteristic_array ;
    int n = arr.size() ;
    vector<int> m(2*n, 0); 

    // phase - 1  
    // cout<<"------------------ PHASE 1--------------------"<<endl ;
    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i = 0 ; i<m.size() ; i++){
        m[i+n] = arr[i] ;   
    }

    // phase - 2 
    // cout<<"------------------ PHASE 2--------------------"<<endl ;

    int steps = int(log2(arr.size())) + 1;
    // cout<<steps<<" steps will be taken"<<endl ;
    // cout<<m.size()<<endl ;
    for (int i = 1; i <= steps; i++)
    {
        int total_threads = (long long)(arr.size() / (pow(2, i)));
        int offset = arr.size() / pow(2, i);
        int s = offset, e = offset + total_threads;
        // cout<<s<<' '<<e<<endl;
    #pragma omp parallel for num_threads(NUM_THREADS) shared(offset, s, e)
        for (int j = s; j < e; j++)
        {
            m[j] = m[2 * j] + m[2 * j + 1];
        }
    }

    // cout<<"M: "<<' ' ;
    // for(int x: m) cout<<x<<' ' ; 
    // cout<<endl ; 

    // phase - 3
    // cout<<"------------------ PHASE 3--------------------"<<endl ;
    // vector<int> L(n);
    // cout<<"HKHSSN"<<endl ;
    // vector<int> R(2*n); 
    R[0] = 0 ;
    // cout<<"HELLO"<<endl ;

    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i=1 ; i<n ; i++){
        L[i] = m[2*i] ; 
    }
    // cout<<"L: "<<' ' ; 
    // for(int x: L) cout<<x<<' ' ; 
    // cout<<endl ;


    // phase - 4
    // cout<<"------------------ PHASE 4--------------------"<<endl ;
    steps = int(log2(2*NUM_ELEMENTS)) + 1;
    int e = (long long)2, s = 1; 
    for(int i = steps ; i>0 ; i--){
        // cout<<s<<' '<<e<<endl;
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
    // cout<<"R: "<<' ' ; 
    // for(int x: R) cout<<x<<' ' ; 
    // cout<<endl ;

    //phase - 5
    // vector<int> B(n, 0); 
    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i =0 ; i<n ; i++){
        B[i] = R[i+n] + m[i+n]; 
    }
    // cout<<"B: "<<' ' ; 
    // for(int x: B) cout<<x<<' ' ; 
    // cout<<endl ;


    #pragma omp parallel for num_threads(NUM_THREADS)
    for(int i = 0 ; i<2*NUM_ELEMENTS ; i++){
        if(characteristic_array[i] == 1) ANS[B[i]-1] = ans[i] ;
    }

    // cout<<"ANS: "<<' ' ; 
    // for(int x: ANS) cout<<x<<' ' ;
    // cout<<endl ;

    vector<int> soln(NUM_ELEMENTS); 
    int nums_less_than_equal = 0;
    int indx = x; 
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

    for(int i = 0 ; i<soln.size() ; i++){
        if(soln[i] != v[i]){
            cout<<"NOT MATCH"<<endl ; 
            return 0; 
        }
    }
    cout<<"MATCH"<<endl ;

    return 0; 
}
