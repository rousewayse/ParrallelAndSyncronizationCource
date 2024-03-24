#include <stdio.h>
#include <omp.h>
int n;
#pragma omp threadprivate(n)
int main(int argc, char *argv[])
{
   int num;
   n=1;
#pragma omp parallel private (num)
   {
      num=omp_get_thread_num();
      printf("�������� n �� ���� %d (�� �����): %d\n", num, n);
      /* �������� ���������� n ����� ������� ���� */
      n=omp_get_thread_num();
      printf("�������� n �� ���� %d (�� ������): %d\n", num, n);
   }
   printf("�������� n (��������): %d\n", n);
#pragma omp parallel private (num)
   {
      num=omp_get_thread_num();
      printf("�������� n �� ���� %d (��� ���): %d\n", num, n);
   }
}
