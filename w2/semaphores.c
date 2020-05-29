#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// binary semaphore implementation

sem_t m; //mutex

void* thread(void* arg){
  // wait
  sem_wait(&m);
  printf("Entered..\n");

  // critical section
  printf("Critical Section\n");
  
  // signal
  printf("Just Exiting...\n");
  sem_post(&m);
}


int main(){
  //initialize as binary semaphore
  sem_init(&m, 0, 1);

  /*enough linux blogs I found said that using fork() was so error prone
  * that it was best to not use it at all, and this approach seemed
  * more safe. */
  //predefine the threads that want access
  pthread_t t1,t2,t3;
  
  pthread_create(&t1,NULL,thread,NULL);
  pthread_create(&t2,NULL,thread,NULL);
  pthread_create(&t3,NULL,thread,NULL);
  
  
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  
  sem_destroy(&m);
  printf("Semaphore destroyed, all done.\n");
  return 0;
}
