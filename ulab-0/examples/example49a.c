#include <stdio.h>
int n;
#pragma omp threadprivate(n)
int main(int argc, char *argv[])
{
   n=1;
#pragma omp parallel copyin(n)
   {
      printf("�������� n: %d\n", n);
   }
}
