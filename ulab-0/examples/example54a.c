#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   int n;
#pragma omp parallel private(n)
   {
      n=omp_get_thread_num();
#pragma omp sections
      {
#pragma omp section
         {
            printf("������ ������, ������� %d\n", n);
         }
#pragma omp section
         {
            printf("������ ������, ������� %d\n", n);
         }
#pragma omp section
         {
            printf("������ ������, ������� %d\n", n);
         }
      }
      printf("������������ �������, ������� %d\n", n);
   }
}
