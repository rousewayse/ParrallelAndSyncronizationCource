#include <stdio.h>
int main(int argc, char *argv[])
{
   printf("���������������� ������� 1\n");
#pragma omp parallel
   {
      printf("������������ �������\n");
   }
   printf("���������������� ������� 2\n");
}
