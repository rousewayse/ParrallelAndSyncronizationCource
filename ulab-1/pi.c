#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

double f(double x){
	return 1/(1+x*x);
}

int main(int argc, char** argv){
	double pi, sum = 0, term, h;
	int myrank, nprocs, n, i;
	if (argc > 1){	
		n = atoi(argv[1]);
	}
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	if (!myrank && argc < 2){
		printf("Number of iterations -->");
		scanf("%d", &n);
	}
	
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	h  = 1.0/n;
	for (i = myrank + 1; i <= n;  i+=nprocs){
		sum += f(h*(i - 0.5));
	}
	term = 4*h*sum;
	MPI_Reduce(&term, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	if(!myrank){
		printf("Computed value of pi is %.15f\n", pi);
	}
	MPI_Finalize();
	return 0;
}
