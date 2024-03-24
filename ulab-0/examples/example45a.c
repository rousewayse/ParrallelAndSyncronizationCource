#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
   int n=1;
   printf("n � ���������������� ������� (������): %d\n", n);
#pragma omp parallel private(n)
   {
      printf("�������� n �� ���� (�� �����): %d\n", n);
      /* �������� ���������� n ����� ������� ���� */
      n=omp_get_thread_num();
      printf("�������� n �� ���� (�� ������): %d\n", n);
   }
   printf("n � ���������������� ������� (�����): %d\n", n);
}
