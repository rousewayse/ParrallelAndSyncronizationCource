#include <stdio.h>
int main(int argc, char *argv[])
{
   int count = 0;
#pragma omp parallel reduction (+: count)
   {
      count++;
      printf("������� �������� count: %d\n", count);
   }
   printf("����� �����: %d\n", count);
}
