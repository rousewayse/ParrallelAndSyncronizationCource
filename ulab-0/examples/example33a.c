#include <stdio.h>
#include "mpi.h"
static int calls = 0;
static int errors = 0;
void err_function(MPI_Comm *comm, int *err, ...)
{
   if(*err == MPI_ERR_OTHER){
      printf("Error MPI_ERR_OTHER\n");
   }
   else{
      errors++;
      printf("Error code %d\n", *err);
   }
   calls++;
}
int main(int argc, char **argv)
{
   MPI_Errhandler errhandler;
   MPI_Init(&argc, &argv);
   MPI_Comm_create_errhandler(err_function, &errhandler);
   MPI_Comm_set_errhandler(MPI_COMM_WORLD, errhandler);
   MPI_Comm_call_errhandler(MPI_COMM_WORLD, MPI_ERR_OTHER);
   MPI_Errhandler_free(&errhandler);
   printf("Error handler was called %d times, with %d errors\n", calls, errors);
   MPI_Finalize();
}
