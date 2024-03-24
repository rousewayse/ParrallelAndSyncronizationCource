#include <stdio.h>
#include <omp.h>
int main(int argc, char *argv[])
{
   int i, m[10];
   printf("������ m � ������:\n");
   /* �������� ������ m ������ � ���������� ��� */
   for (i=0; i<10; i++){
      m[i]=0;
      printf("%d\n", m[i]);
   }
#pragma omp parallel shared(m)
   {
      /* �������� 1 �������� ������� m, ����� ��������
      ��������� � ������� ������� ���� */
      m[omp_get_thread_num()]=1;
   }
   /* ��� ��� ���������� ������ */
   printf("������ m � �����:\n");
   for (i=0; i<10; i++) printf("%d\n", m[i]);
}
