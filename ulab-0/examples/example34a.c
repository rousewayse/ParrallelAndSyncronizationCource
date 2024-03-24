#include <stdio.h>
int main(){
#ifdef _OPENMP
   printf("OpenMP is supported! %d\n", _OPENMP);
#endif
}
