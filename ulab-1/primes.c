#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <mpi.h>




int* alloc_basic_primes(int n){
	size_t upper_limit = (size_t)sqrt(n);
	return malloc(sizeof(int)*upper_limit+1);
}

int  find_basic_primes(int n, int* primes, size_t* primes_size){
	
	size_t upper_limit = (size_t)sqrt(n);
	//primes = malloc(sizeof(int)*(upper_limit+1));
	primes[0] = 1;
	*primes_size = 1;
	if (n > 1) {
		primes[1] = 2;
		*primes_size = 2;
	}	
	for (size_t i = 3; i <= upper_limit; ++i){
		//Все четные кроме двойки -- точно не простые
		if ((i % 2 == 0) ){
			continue;
		}
		int i_is_not_prime = 0;
		for (size_t k = 1; k < *primes_size; ++k ){
			if (i % primes[k] == 0){
				i_is_not_prime = 1;
				break;
			}
		}
		if (!i_is_not_prime){
			primes[(*primes_size)++] = i;
		}

	}
	return upper_limit+1;	
}


int check_prime(int number, int* basic_primes, int basic_primes_num){
	for (size_t i=1; i < basic_primes_num; ++i){
		if (number % basic_primes[i] == 0){
			return 0;
		}
	}
	return 1;
}


size_t find_primes_num(int start, int stop, int step, int procn,  int* basic_primes, int basic_primes_num){
	size_t primes_num = 0;
	int start_ = start/2;
	int k = 2*(start_ + procn)+1; 
	for (int i = 1; k  <= stop; ++i){
		if (check_prime(k, basic_primes, basic_primes_num)){
			primes_num++;
		}
		k = 2*(start_ + procn + i*step)+1;
	}
	return primes_num;
}


int  main(int argc, char** argv){
	int N = atoi(argv[1]); 
	size_t primes_num = 0;
	int* primes = alloc_basic_primes(N);
	//int start = find_basic_primes(N, &primes, &primes_num);	
	
	int myrank, nprocs, start;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	if (!myrank){
		printf("Process [%d]: Initializing basic primes array...\n", myrank);
		start = find_basic_primes(N, primes, &primes_num);	
		printf("Process [%d]: Initializing done\nProcess [%d]: Bcasting basic primes array...\n", myrank, myrank);
	}
	MPI_Bcast((int*)&primes_num, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&start, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(primes, primes_num, MPI_INT, 0, MPI_COMM_WORLD);
	printf("Process [%d]: received basic primes array\n", myrank);
	MPI_Barrier(MPI_COMM_WORLD);
	if (!myrank){
		printf("Process [%d]: Done Bcasting\n", myrank);
	}
	int proc_res = (int)find_primes_num(start, N, nprocs, myrank,  primes, (int)primes_num);
	MPI_Barrier(MPI_COMM_WORLD);
	printf("\tProcess %d forund primes %d\n", myrank, proc_res);	
	int res = 0;
	MPI_Reduce(&proc_res, &res, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (myrank == 0){
		printf("Found %d primes in [1, %d]\n", primes_num+res, N);
	}
	free(primes);	
	MPI_Finalize();
	return 0;
}
