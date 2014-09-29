//
//  main.c
//  asst3skeleton
//
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// The consumer function
void *consume(void *param);

// Global mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Global struct to share data
typedef struct{
  int * buffer;
  int index_last_elem;
} shared_storage_t;

// Instantiate shared_storage
shared_storage_t shared_storage;


int prodcons(int count) {
  // Initialize shared_storage
  shared_storage.buffer = malloc(sizeof(1)*count);
  shared_storage.index_last_elem = -1;
  
  pthread_t consumer_thread;
  pthread_create(&consumer_thread, NULL, consume, &shared_storage);
  
  
  while(1){
    ///BEGIN CRITICAL SECTION///
    pthread_mutex_lock(&mutex);
    
    if (shared_storage.index_last_elem < count){
      if (shared_storage.index_last_elem != -1)
        printf("Producer: current index = %d\n", shared_storage.index_last_elem);
      
      // Increment index_last_elem
      shared_storage.index_last_elem++;
      
      // Add number to new buffer[index_last_elem]
      shared_storage.buffer[shared_storage.index_last_elem] = shared_storage.index_last_elem;
      
      printf("Producer: shared_storage[%d] = %d\n", shared_storage.index_last_elem, shared_storage.buffer[shared_storage.index_last_elem]);
      printf("Producer: updated index of last element: %d\n\n", shared_storage.index_last_elem);
    }
    ///END CRITICAL SECTIOn
    pthread_mutex_unlock(&mutex);
  }
  
  //Never reached...
  free(shared_storage.buffer);
  return 0;
}


int main(int count){
  // TO-DO Replace 2000 with count
  prodcons(2000);
}


void *consume(void *param){
  shared_storage_t *shared_storage = (shared_storage_t *)param;
  while(1){
    ///BEGIN CRITICAL SECTION///
    pthread_mutex_lock(&mutex);
    
    if (shared_storage->index_last_elem > 0){
      printf("Consumer: current index = %d\n", shared_storage->index_last_elem);
      printf("Consumer: shared_storage[%d] = %d\n", shared_storage->index_last_elem, shared_storage->buffer[shared_storage->index_last_elem]);
      
      // Decrement index_last_elem
      shared_storage->index_last_elem--;
      
      printf("Consumer: updated index of last element: %d\n\n", shared_storage->index_last_elem);
    }
    ///END CRITICAL SECTION///
    pthread_mutex_unlock(&mutex);
  }
}
