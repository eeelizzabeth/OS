
/* 
 * A parallel merge sort using pthreads
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct sort_args_t {
  float *x;	  // array to be sorted
  int len;	  // length of array
} Sort_args;

// sort and return float array x, of length n
// using gnome sort
float *gsort(float *x, int n) {
  int i = 0;
  while (i < n) {
    if (i == 0 || x[i] >= x[i-1]) {
      i++;
    } else {
      // swap x[i] and x[i-1]
      float temp = x[i];
      x[i] = x[i-1];
      x[i-1] = temp;
  
      i--;
    }
  }
  return x;
}

// return a new array obtained by merging arrays
// x and y, where m is the length of x and n
// is the length of y.  The input arrays are
// assumed to be sorted.  If they are, the output
// will be sorted.
float *merge(float *x, int m, float *y, int n) {
  
  // x and y are merged into new array z
  float *z = (float *)malloc((m + n)*(sizeof(float)));

  int i = 0;   // index into x
  int j = 0;   // index into y
  int k = 0;   // index into z
  while (i < m || j < n) {
    // pick the x element if there are no more y's, or
    // if there are x's and y's and the x value is smaller
    if (j == n || (i < m && x[i] < y[j])) {
      z[k] = x[i];
      i++;
    } else {
      z[k] = y[j];
      j++;
    }
    k++;
  }
  return z;
}

// sort and return float array x, of length n
// using merge sort
void *pmerge_sort(void *args) {

  // unpack arguments
  Sort_args *sargs = (Sort_args *)args;
  float *x = sargs->x;
  int n = sargs->len;
  
  // if n < k, the array is sorted directly
  // using another sort algorithm
  int k = 100;
  if (n < k) {
    return(gsort(x, n));
  }

  // create 2 threads; each sorts half the data
  int m = ((float)n)/2.0;

  // pack arguments to recursive call
  Sort_args args1, args2;
  args1.x = x;
  args1.len = m;
  args2.x = &x[m];
  args2.len = n-m;

  float *p1 = pmerge_sort((void *)&args1);

  int rc;
  pthread_t  p2;
  rc = pthread_create(&p2, NULL, pmerge_sort, (void *)&args2);  assert(rc == 0);
  
  // merge the results from the threads
  float *x2;
  pthread_join(p2, (void **) &x2); 
  float *y = merge(p1, m, x2, n-m);

  // copy the result back to x and free y
  memcpy((void *)x, (void *)y, n*sizeof(float));
  free(y);

  return (void *)x;
}

// sort array x 
void merge_sort(float *x, int n) {
  // call recursive helper function
  Sort_args args;
  args.x = x;
  args.len = n;
  pmerge_sort((void *)&args);
}

