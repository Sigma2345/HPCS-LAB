#include<bits/stdc++.h>
using namespace std;
#define N 65536

int main(){

    vector<long long> v(N);
    for (int i = 0; i < N; i++)
        v[i] += rand() % N; 
    long long sum = 0;
    for(int x: v)
        sum += x;

    cout << sum << endl;

    return 0; 
}
