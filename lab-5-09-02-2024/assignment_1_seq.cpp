#include <bits/stdc++.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 4
#define NUM_ELEMENTS 1024

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

    int rank = 0 ; 
    for(int i = 0 ; i<v.size() ; i++){
        if(v[i] < x) rank++ ; 
    }

    cout << "rank of element is " << rank + 1 << endl;
    return 0;
}