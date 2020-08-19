#include <stdio.h>
#include <stdlib.h>

// starter code for Problems 4-8 of OSTEP, chapter 14
int main() {
   int *x;

   int *data;
   data = (int *)malloc(100);
   data[100] = 0;
   printf("data[100] = %d\n", data[100]);

   //x = (int *)malloc(10 * sizeof(int));
   //x[0] = 1;
   //x[1] = 2;
   //printf("x[1] = %d\n", x[1]);

   return 0;
}

