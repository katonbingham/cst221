/*
 * Author: Katon Bingham
 * Date: 06/4/2020
 * CST221 
 * Application to model producer/consumer relationship with threads.
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
/*

#include <sys/mman.h>
#include <errno.h>
*/
#define BUF_SIZE 10 // arbitrary size
int buffer[BUF_SIZE]; // buffer
int theProduct = 0; // arbitrary filling for the buffer
unsigned int count = 0;

int produce(){
  return theProduct++;
}

void consume(int i){
  buffer[count] = (count-1); 
}

void producer(void){
  while (1){
    while (count == BUF_SIZE){
      // buffer is full
      printf("count is %d, producer sleep\n", count);
      sleep(1);
    }
    // write to buffer BEFORE incrementing count
    buffer[count] = produce();
    printf("produce, count is %d\n", count); 
    ++count;
    sleep(1);
  }
}

void consumer(void){
  while(1){
    while (count == 0){
      // buffer is empty
      printf("count is %d, consumer sleep\n", count);
      sleep(1);
    }
    consume(buffer[count]);
    printf("consume %d\n", count);
    --count;
    sleep(1);
  }
}

int main(){
  pthread_t thread[3];
  int thread_id[3] = {0,1,2};
  
  pthread_create(&thread[0], NULL, (void *)consumer, &thread_id[0]);
  pthread_create(&thread[1], NULL, (void *)producer, &thread_id[1]);
  pthread_create(&thread[2], NULL, (void *)producer, &thread_id[2]);

  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  pthread_join(thread[2], NULL);

  return 0;
}
