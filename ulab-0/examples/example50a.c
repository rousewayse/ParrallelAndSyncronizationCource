#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   int count, num;
#pragma omp parallel
   {
      count=omp_get_num_threads();
      num=omp_get_thread_num();
      if (num == 0) printf("����� �����: %d\n", count);
      else printf("���� ����� %d\n", num);
   }
}
