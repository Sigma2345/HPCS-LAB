#include<iostream>
#include <omp.h>
#include <stdio.h>
using namespace std;
#define rep for (long i = 0; i < 1e9; i++){}

void consume(int &numt, int &tid){
    cout << "(numt_val)=" << numt << " (tid_val)=" << tid << endl;
    cout << "(numt)=" << &numt << " (tid)=" << &tid << endl;
}

int main()
{

    int numt = 0, tid = 0;
    cout << "from outside (numt)=" << &numt << " (tid)="<<&tid<<endl ; 
#pragma omp parallel shared(numt) firstprivate(tid)
    {
        rep
        #pragma omp critical        
        consume(numt, tid);
    }
    return 0;
}
