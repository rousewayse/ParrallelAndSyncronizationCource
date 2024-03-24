#include <stdio.h>
#include <mpi.h>
double f(double y) {return(4.0/(1.0+y*y));}
int main(int argc, char* argv[])
{
   double w, x, sum, locpi, pi, t1, t2;
   int i, rank, size;
   int n = 1000000000;
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Barrier(MPI_COMM_WORLD);
   t1=MPI_Wtime();
   w = 1.0/(double)n;
   sum = 0.0;
   for(i=rank+1; i <= n; i+=size)
   {
      x = w*(i-0.5);
      sum = sum + f(x);
   }
   locpi = w*sum;
   MPI_Reduce(&locpi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Barrier(MPI_COMM_WORLD);
   t2=MPI_Wtime();
   if(rank==0) printf("N= %d, Nproc=%d, pi = %lf, Time=%lf \n", n, size, pi, t2-t1);
   MPI_Finalize();
}
