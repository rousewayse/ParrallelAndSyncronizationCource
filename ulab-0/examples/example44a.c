#include <stdio.h>
int main(int argc, char *argv[])
{
   int n;
#pragma omp parallel private(n)
   {
      n=1;
#pragma omp master
      {
         n=2;
      }
      printf("������ �������� n: %d\n", n);
#pragma omp barrier
#pragma omp master
      {
         n=3;
      }
      printf("������ �������� n: %d\n", n);
   }
}
