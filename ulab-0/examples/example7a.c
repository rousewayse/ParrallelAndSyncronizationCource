#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
   int size, rank, next, prev, rbuf;
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   next = rank+1;
   if(next == size) next = MPI_PROC_NULL;
   MPI_Send(&rank, 1, MPI_INT, next, 5, MPI_COMM_WORLD);
   prev = rank-1;
   if(prev == -1) prev = MPI_PROC_NULL;
   rbuf = -1;
   MPI_Recv(&rbuf, 1, MPI_INT, prev, 5, MPI_COMM_WORLD, &status);
   printf("process %d rbuf = %d\n", rank, rbuf);
   MPI_Finalize();
}
