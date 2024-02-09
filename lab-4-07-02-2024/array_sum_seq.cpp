#include<bits/stdc++.h>
using namespace std;
#define N 1024*65536

int main(){

    vector<long long> v(N);
    for (int i = 0; i < N; i++)
        v[i] = 1;

    vector<long long> ans(2 * N, -1);
    for (int i = N - 1; i >= 0; i--)
    {
        ans[i + N] = v[i];
    }

    long long sum = 0;
    for(int x: v)
        sum += x;

    cout << sum << endl;

    return 0; 
}
