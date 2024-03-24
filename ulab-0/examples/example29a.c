#include <stdio.h>
#include "mpi.h"
int main(int argc, char **argv)
{
   int rank, size, prev, next, ranks[2];
   int buf[2];
   MPI_Aint lb, extent;
   MPI_Win win;
   MPI_Group group, commgroup;
   MPI_Init(&argc, &argv);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   prev = rank - 1;
   next = rank + 1;
   if(rank==0) prev = size - 1;
   if(rank==size - 1) next = 0;
   MPI_Type_get_extent(MPI_INT, &lb, &extent);
   MPI_Win_create(buf, 2*extent, extent, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
   MPI_Comm_group(MPI_COMM_WORLD, &group);
   ranks[0]=prev; ranks[1]=next;
   MPI_Group_incl(group, 2, ranks, &commgroup);
   MPI_Win_post(commgroup, 0, win);
   MPI_Win_start(commgroup, 0, win);
   MPI_Put(&rank, 1, MPI_INT, prev, 1, 1, MPI_INT, win);
   MPI_Put(&rank, 1, MPI_INT, next, 0, 1, MPI_INT, win);
   MPI_Win_complete(win);
   MPI_Win_wait(win);
   MPI_Win_free(&win);
   MPI_Group_free(&group);
   MPI_Group_free(&commgroup);
   printf("process %d prev = %d next=%d\n", rank, buf[0], buf[1]);
   MPI_Finalize();
}
