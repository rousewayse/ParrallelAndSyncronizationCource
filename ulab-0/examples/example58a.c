#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
#pragma omp parallel
   {
      printf("��������� 1\n");
      printf("��������� 2\n");
#pragma omp barrier
      printf("��������� 3\n");
   }
}
