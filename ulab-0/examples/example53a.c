#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   int i;
#pragma omp parallel private(i)
   {
#pragma omp for schedule (static, 6)
//#pragma omp for schedule (dynamic, 6)
//#pragma omp for schedule (guided, 6)
      for (i=0; i<200; i++)
      {
         printf("���� %d ��������� �������� %d\n",
                omp_get_thread_num(), i);
         //sleep(1);
      }
   }
}
