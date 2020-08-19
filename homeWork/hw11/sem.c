/* 
 * Implementation of a semaphore using locks and condition
 * variables.  
 *
 * Complete the code below by adding code where you see
 * YOUR CODE HERE.  Do not modify the code in any other way.
 *
 * Follow the Anderson/Dahlin method in designing the semaphore
 * object.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NUMOPS 10000

typedef struct {

  // YOUR CODE HERE (add state and synchronization variables to struct)
	
  int value;
  
  pthread_mutex_t lock;
  pthread_cond_t sig;

} SEM;

// contructor of semaphore
// parameter a is the initial value of the semaphore
SEM *sem_create(int a) {
  SEM *sem;
  sem = (SEM *)malloc(sizeof(SEM));
  assert(sem != NULL);

  sem->value = a; 
  pthread_mutex_init(&sem->lock, NULL);
  pthread_cond_init(&sem->sig, NULL);

  return(sem);
}

// wait operation on semaphore
void sem_wait(SEM *sem) {

  pthread_mutex_lock(&sem->lock);
  
  while(sem->value <= 0 ) {
    pthread_cond_wait(&sem->sig, &sem->lock);
  }

  sem->value--;
  pthread_mutex_unlock(&sem->lock);
}

void sem_signal(SEM *sem) {

  pthread_mutex_lock(&sem->lock);
  sem->value++;

  pthread_cond_signal(&sem->sig);
  pthread_mutex_unlock(&sem->lock);
  
}

/*
 * The following code tests the semaphore implementation.
 * Four threads all try to access a critical section; the semaphore
 * should allow at most 2 threads in the critical section at once
 * (assuming that sem_init has its default value of 2).
 */

// repeatedly enter and exit critical section
void *agent(void *arg) {
  SEM *sem = (SEM *)arg;
  int i;
  for (i = 0; i < NUMOPS; i++) {
    sem_wait(sem);
    // beginning of critical section
    printf("in\n"); 
    int j; for (j = 0; j < 5000; j++);   // wait so others can enter critical section
    printf("out\n");
    // end of critical section
    sem_signal(sem);
  } 
  pthread_exit(NULL);
}

// test the semaphore
// note that the initial semaphore value can be provided on the command line
int main(int argc, char *argv[]) {
  int sem_init;
  pthread_t t1,t2,t3,t4;

  sem_init = 2;
  if (argc > 1) {
     // if input param
     sem_init = atoi(argv[1]);
  }

  SEM *sem = sem_create(sem_init);
  pthread_create(&t1, NULL, agent, (void *)sem);
  pthread_create(&t2, NULL, agent, (void *)sem);
  pthread_create(&t3, NULL, agent, (void *)sem);
  pthread_create(&t4, NULL, agent, (void *)sem);

  pthread_exit(NULL);
}
