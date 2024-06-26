#include "mpi.h"
#include <stdio.h>
int main(int argc, char **argv)
{
   int BUFSIZE = sizeof(int) + MPI_BSEND_OVERHEAD;
   char *buf;
   int rank, ibufsize, rbuf, size;
   MPI_Status status;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   if(rank == 0){
      MPI_Buffer_attach(malloc(BUFSIZE), BUFSIZE);
      MPI_Bsend(&rank, 1, MPI_INT, 1, 5, MPI_COMM_WORLD);
      MPI_Buffer_detach(&buf, &ibufsize);
      free(buf);
   }
   if(rank == 1){
      MPI_Recv(&rbuf, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
      printf("Process 1 received %d from process %d\n", rbuf, status.MPI_SOURCE);
   }
   MPI_Finalize();
}
