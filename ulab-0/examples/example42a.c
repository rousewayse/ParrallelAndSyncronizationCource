#include <stdio.h>
int main(int argc, char *argv[])
{
#pragma omp parallel
   {
      printf("��������� 1\n");
#pragma omp single nowait
      {
         printf("���� ����\n");
      }
      printf("��������� 2\n");
   }
}
