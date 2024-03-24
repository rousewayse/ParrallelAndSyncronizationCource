#include <stdio.h>
#include <omp.h>
#define NTASKS 5
void work(int num){
   printf("Процесс %d ожидает\n", num);
   //sleep(1);
}
int main(int argc, char *argv[])
{
   omp_lock_t lock;
   int n=NTASKS, i, num;
   omp_init_lock(&lock);
#pragma omp parallel private(i, num) 
   {
      num=omp_get_thread_num();
      for(i = 0; i < n; i++)
#pragma omp task
      {
         work(num);
         while(!omp_test_lock(&lock)){
#pragma omp taskyield
         }
         printf("Процесс %d в критической секции\n", num);
         //sleep(2);
         omp_unset_lock(&lock);
      }
   }
}
