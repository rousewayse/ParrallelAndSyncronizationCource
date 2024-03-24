#include <stdio.h>
#include <omp.h>
double f(double y) {return(4.0/(1.0+y*y));}
int main()
{
   double w, x, sum, pi, t1, t2;
   int i, size;
   int n = 1000000000;
   t1=omp_get_wtime();
   w = 1.0/(double)n;
   sum = 0.0;
#pragma omp parallel private(x) shared(w)
   {
      size=omp_get_num_threads();
#pragma omp for reduction(+:sum)
      for(i=1; i <= n; i++)
      {
         x = w*(i-0.5);
         sum = sum + f(x);
      }
   }
   pi = w*sum;
   t2=omp_get_wtime();
   printf("N= %d, Nproc=%d, pi = %lf, Time=%lf \n", n, size, pi, t2-t1);
}
