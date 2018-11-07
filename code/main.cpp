#include "Sequential/HashTable.h"
#include "FineGrained/FineHashTable.h"
#include <cassert>
#include <pthread.h>
#define THREAD_COUNT 4
#define BUCKET_COUNT 500
#define ITER_COUNT 10000
FineHashTable h(BUCKET_COUNT);

//Checks if the hash table has the values it should at any given point
void *checkConsistency(void *threadNumber) {
    int32_t threadNum = *((int32_t *)threadNumber);

    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        h.insertItem(index);
        bool result = h.findItem(index);
        assert(result);
    }
    
    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        h.deleteItem(index);
        assert(!h.findItem(index));
    }

    return nullptr;
}

int main() 
{ 
  pthread_t threads[THREAD_COUNT];
  uint32_t threadNum[THREAD_COUNT];
  for(int i = 0; i < THREAD_COUNT; i++) {
    pthread_create(&threads[i], NULL, checkConsistency, (void *)&(threadNum[i]));
  }
  for(int i = 0; i < THREAD_COUNT; i++)
    pthread_join(threads[i], NULL);
  cout << "Hash Table behaves as it should.\n";
  return 0; 
}