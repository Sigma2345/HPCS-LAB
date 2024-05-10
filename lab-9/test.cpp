#include <stdio.h>
#include <omp.h>
#include <unistd.h>
int main() {
int x,y;
#pragma omp parallel num_threads(10) 
{
#pragma omp single nowait
 {
#pragma omp task depend (out:x)  //task1
  {
        x=1;
        printf("task1  thread id: %d\n", omp_get_thread_num()); 
  }
#pragma omp task depend(in:x) depend(out:y)  //task2
  {
        // sleep(2); //Does task3 wait for us? Yes!
        y=x+1;
        printf("task2 thread id: %d\n", omp_get_thread_num()); 
  }
#pragma omp task depend (inout:x)  //task3
  {
        x++;
        printf("task3(x): %d thread id: %d\n" , x, omp_get_thread_num());
  }
#pragma omp task depend (in:x,y)  //task4
 {
        printf("task4 (x+y): %d thread id: %d\n" , x+y, omp_get_thread_num());
 }
 }
}
return 0;
}