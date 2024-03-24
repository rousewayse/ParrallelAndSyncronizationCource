#include <stdio.h>
int main(int argc, char *argv[])
{
#pragma omp parallel
   {
      printf("Сообщение 1\n");
#pragma omp single nowait
      {
         printf("Одна нить\n");
      }
      printf("Сообщение 2\n");
   }
}
