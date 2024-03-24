#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   int n=0;
#pragma omp parallel
   {
#pragma omp sections lastprivate(n)
      {
#pragma omp section
         {
            n=1;
         }
#pragma omp section
         {
            n=2;
         }
#pragma omp section
         {
            n=3;
         }
      }
      printf("�������� n �� ���� %d: %d\n",
             omp_get_thread_num(), n);
   }
   printf("�������� n � ���������������� �������: %d\n", n);
}
