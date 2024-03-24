#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[])
{
   int n=1;
   printf("n в последовательной области (начало): %d\n", n);
#pragma omp parallel private(n)
   {
      printf("«начение n на нити (на входе): %d\n", n);
      /* ѕрисвоим переменной n номер текущей нити */
      n=omp_get_thread_num();
      printf("«начение n на нити (на выходе): %d\n", n);
   }
   printf("n в последовательной области (конец): %d\n", n);
}
