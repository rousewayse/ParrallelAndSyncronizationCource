#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   printf("�������� OMP_DYNAMIC: %d\n", omp_get_dynamic());
   omp_set_dynamic(1);
   printf("�������� OMP_DYNAMIC: %d\n", omp_get_dynamic());
#pragma omp parallel num_threads(128)
   {
#pragma omp master
      {
         printf("������������ �������, %d �����\n",
                omp_get_num_threads());
      }
   }
}
