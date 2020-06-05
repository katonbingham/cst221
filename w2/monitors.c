/* Monitor implementation in C 
 * Author: Katon Bingham
 * Date: 05/29/2020
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// monitor implementation

// replace with actual mutex?
sem_t mutex;     //global mutex for lock/unlock
int counter;     //global counter to do work on
pthread_t id[2]; //threads to work in

void* criticalSection(){
  sem_wait(&mutex); //lock mutex while working counter

  printf("Critical section %d", counter);
  
  for(int i=0; i<10;i++); //arbitrary work

  printf("\nCritical section %d finished\n", counter);
  
  counter += 1; //advance thread counter
  sem_post(&mutex); //unlock mutex

}

int main(){
  //initialize binary semaphore as simple mutex
  sem_init(&mutex, 0, 1);
  int i = 0;

  //create threads
  while(i<2){
    pthread_create(&id[i],NULL,&criticalSection,NULL);
    i++;
  }

  
  pthread_join(id[0], NULL);
  pthread_join(id[1], NULL);

  sem_destroy(&mutex);
  return 0;
}
