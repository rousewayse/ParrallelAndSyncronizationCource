#define N 4096
int main()
{
   int i, j, k;
   double s;
/* Выделение памяти под матрицы */
   double **a=(double**)malloc(sizeof(double*)*N);
   for(i=0; i<N; i++)
      a[i]=(double*)malloc(sizeof(double)*N);
   double **b=(double**)malloc(sizeof(double*)*N);
   for(i=0; i<N; i++)
      b[i]=(double*)malloc(sizeof(double)*N);
   double **c=(double**)malloc(sizeof(double*)*N);
   for(i=0; i<N; i++)
      c[i]=(double*)malloc(sizeof(double)*N);
// Инициализация матриц
   for(i=0; i<N; i++)
      for(j=0; j<N; j++){
         a[i][j]=(i+j)*0.0001e0;
         b[i][j]=(i-j)*0.0001e0;
         c[i][j]=0.0e0;
      }
// Основной вычислительный блок
   for(i=0; i<N; i++)
      for(j=0; j<N; j++)
         for(k=0; k<N; k++) c[i][j]+=a[i][k]*b[k][j];
/* Вычисление контрольной суммы и печать результата */
   for(i=0, s=0.0e0; i<N; i++)
      for(j=0; j<N; j++)
         s+=c[i][j];
   printf("N= %d, Sum=%lf\n", N, s);
}
