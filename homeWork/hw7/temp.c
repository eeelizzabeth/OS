#include <stdio.h>
#include <stdlib.h>
#include "random_cache.h"

//
// A simple data store with cache
//

#define DATA_SIZE 1000
#define CACHE_SIZE 10

//
// Data is stored in array data[]
//

float data[DATA_SIZE];

int nhits = 0;
int nmisses = 0;
CACHE *cache;

// initialize the data array
void init() {
   int i;

   // initialize data
   for (i = 0; i < DATA_SIZE; i++) {
      data[i] = ((float)i)/2.0;
   }

   // create cache
   cache = cache_new(CACHE_SIZE);
}

// get the ith data value
float get(int i) {
  if (i < 0 || i >= DATA_SIZE) {
     fprintf(stderr, "get: no data element %d\n", i);
     exit(EXIT_FAILURE);
  }

  float x = cache_lookup(cache, i);
  if (x >= 0) {
    // cache hit
    nhits++;

    return x;
  } else {
    // cache miss
    nmisses++;

    x = data[i];
    cache_insert(cache, i, x);
    return data[i];
  }
}

// set the ith data value to x
void set(int i, float x) {
  if (i < 0 || i >= DATA_SIZE) {
    fprintf(stderr, "set: no data element %d\n", i);
    exit(EXIT_FAILURE);
  }

  data[i] = x;

  // clear cache entry
  cache_clear(cache, i);
}

// simulate a lot of data accesses
int main(int argc, char *argv[]) {

  // simulation parameters
  int num_accesses = 100000;
  int dist_size = 10;
  int move_size1[] = {-3,-2,-1,0,0,0,0,1,2,3};
  int move_size2[] = {-5,-4,-3,-2,-1,1,2,3,4,5};

  init();

  int i,j,delta;
  j = 0;
  for (i = 0; i < num_accesses; i++) {
     // randomly get a new data element j to access, based
     // on a change from the last element that was accessed
     delta = move_size1[rand() % dist_size];
     j += delta;
     if (j < 0) {
        j = 0;
     } else if (j >= DATA_SIZE) {
        j = DATA_SIZE - 1;
     }

     get(j);
  }
  printf("Hits: %d\n", nhits);
  printf("Miss: %d\n", nmisses);

  exit(0);
}
