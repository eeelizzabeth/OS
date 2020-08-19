
typedef struct cache {
  int size; //number of cache elements
  int *addr; //index of element
  float *data; //value of element 
} CACHE;
   
CACHE *cache_new(int size);
float  cache_lookup(CACHE *cache, int i);
void   cache_insert(CACHE *cache, int i, float x);
void   cache_clear(CACHE *cache, int i);


