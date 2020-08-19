#include <stdlib.h>
#include "random_cache.h"

//
// A simple cache for positive float values, with a random replacement policy
//

CACHE *cache_new(int size) {
  CACHE *cache = malloc(sizeof(CACHE));
  cache->size = size;
  cache->addr = malloc(size * sizeof(int));
  cache->data = malloc(size * sizeof(float));

  // initialize -- an addr value of -1 means the cache element is unused
  int i;
  for (i = 0; i < cache->size; i++) {
    cache->addr[i] = -1;
  }
  
  return cache;
}

// return value of data element i if it is cached; else return -1
float cache_lookup(CACHE *cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
     if (cache->addr[j] == i) {
       // cache hit
       return cache->data[j];
     }
  }
  // cache miss
  return -1.0;
}

// record in the cache that the ith data element has value x
// a random replacement policy is used
void cache_insert(CACHE *cache, int i, float x) {
  int j = rand() % cache->size;
  cache->addr[j] = i;
  cache->data[j] = x;
}

// clear the ith element of the cache
void cache_clear(CACHE *cache, int i) {
  int j;
  for (j = 0; j < cache->size; j++) {
     if (cache->addr[j] == i) {
        cache->addr[j] = -1;
        break;
     }
  }
}

