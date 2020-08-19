
/* 
 * a pthreads readers/writers lock 
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUMOPS 50000

typedef struct {
  // sync. variables
  pthread_mutex_t lock;
  pthread_cond_t read_go;
  pthread_cond_t write_go; 
  
  // state variables
  int active_readers;
  int active_writers;
  int waiting_readers;
  int waiting_writers;
} RWLOCK;

RWLOCK *rwlock_create() {
  // initialize state variables
  RWLOCK *rwlock;
  rwlock = malloc(sizeof(RWLOCK));
  assert(rwlock != NULL);
  rwlock->active_readers = 0;
  rwlock->active_writers = 0;
  rwlock->waiting_readers = 0;
  rwlock->waiting_writers = 0;

  // initialize synchronization variables
  pthread_mutex_init(&rwlock->lock, NULL);
  pthread_cond_init(&rwlock->read_go, NULL);
  pthread_cond_init(&rwlock->write_go, NULL);

  return(rwlock);
}

// diagnostic code -- use as you like
// enable by using 1 instead of 0 in 'if' condition
void print_state(char *id, RWLOCK *rwlock) {
  if (0) {
    printf("%s: wr=%d, ar=%d, ww=%d, aw=%d\n", id,
         rwlock->waiting_readers, rwlock->active_readers,
         rwlock->waiting_writers, rwlock->active_writers);
  }
}

void start_read(RWLOCK *rwlock) {
  pthread_mutex_lock(&rwlock->lock);
  print_state("sr1", rwlock);

  rwlock->waiting_readers++;

  while( rwlock->waiting_readers == 0 || rwlock->active_writers > 0) {
	pthread_cond_wait(&rwlock->read_go, &rwlock->lock);	
  }

  pthread_cond_signal(&rwlock->read_go);

  rwlock->waiting_readers--;
  rwlock->active_readers++;
  
  print_state("sr2", rwlock);
  pthread_mutex_unlock(&rwlock->lock);
}

void done_read(RWLOCK *rwlock) {
  pthread_mutex_lock(&rwlock->lock);
  print_state("dr1", rwlock);

  rwlock->active_readers--;
  if (rwlock->waiting_writers != 0 && rwlock->active_writers == 0) {
    pthread_cond_signal(&rwlock->write_go);
  }

  print_state("dr2", rwlock);
  pthread_mutex_unlock(&rwlock->lock);
}

void start_write(RWLOCK *rwlock) {
  pthread_mutex_lock(&rwlock->lock);
  print_state("sw1", rwlock);

  rwlock->waiting_writers++;
  while(rwlock->active_readers != 0 || rwlock->active_writers != 0)
  {
     pthread_cond_wait(&rwlock->write_go,&rwlock->lock);  
  }
 
  rwlock->waiting_writers--;
  rwlock->active_writers++;

  print_state("sw2", rwlock);
  pthread_mutex_unlock(&rwlock->lock);
}

void done_write(RWLOCK *rwlock) {
  pthread_mutex_lock(&rwlock->lock);
  print_state("dw1", rwlock);

  rwlock->active_writers--;
  pthread_cond_signal(&rwlock->write_go);	  
  pthread_cond_signal(&rwlock->read_go);

  print_state("dw2", rwlock);
  pthread_mutex_unlock(&rwlock->lock);
}

// reader: does a bunch of reads
void *reader(void *arg) {
  RWLOCK *rwlock = (RWLOCK *)arg;
  int i;
  for (i = 0; i < NUMOPS; i++) {
    start_read(rwlock);
    printf("sr\n");
    printf("dr\n");
    done_read(rwlock);
  } 
  pthread_exit(NULL);
}

// writer: does a bunch of writes
void *writer(void *arg) {
  RWLOCK *rwlock = (RWLOCK *)arg;
  int i;
  for (i = 0; i < NUMOPS; i++) {
    start_write(rwlock);
    printf("sw\n");
    printf("dw\n");
    done_write(rwlock);
  } 
  pthread_exit(NULL);
}

// test the read-write lock
int main(int argc, char *argv[]) {
  pthread_t r1,r2,r3,w1,w2;

  RWLOCK *rwlock = rwlock_create();

  // create some reading and writing threads
  pthread_create(&r1, NULL, reader, (void *)rwlock);  
  pthread_create(&r2, NULL, reader, (void *)rwlock);  
  pthread_create(&r3, NULL, reader, (void *)rwlock);  
  pthread_create(&w1, NULL, writer, (void *)rwlock);  
  pthread_create(&w2, NULL, writer, (void *)rwlock);  

  pthread_exit(NULL);
}
