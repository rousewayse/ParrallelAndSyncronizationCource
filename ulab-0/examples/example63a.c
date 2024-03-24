#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   omp_lock_t lock;
   int n;
   omp_init_lock(&lock);
#pragma omp parallel private (n)
   {
      n=omp_get_thread_num();
      while (!omp_test_lock (&lock))
      {
         printf("������ �������, ���� %d\n", n);
         //sleep(2);
      }
      printf("������ �������� ������, ���� %d\n", n);
      //sleep(5);
      printf("����� �������� ������, ���� %d\n", n);
      omp_unset_lock(&lock);
   }
   omp_destroy_lock(&lock);
}
