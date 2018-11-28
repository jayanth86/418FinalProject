#include "Sequential/HashTable.h"
#include "FineGrained/FineHashTable.h"
#include "LockFree/LockFreeHashTable.h"
#include <cassert>
#include <pthread.h>
#define THREAD_COUNT 4
#define BUCKET_COUNT 50
#define ITER_COUNT 10000
FineHashTable f_h(BUCKET_COUNT);
LockFreeHashTable lf_h(BUCKET_COUNT);

// Checks if the hash table has the values it should at any given point
void *checkConsistency(void *threadNumber) {
    int32_t threadNum = *((int32_t *)threadNumber);
    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        f_h.insertItem(index, 0);
        lf_h.insertItem(index, 0);
        bool f_result = f_h.findItem(index);
        bool lf_result = lf_h.findItem(index);
        assert(f_result && lf_result);
    }
    
    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        f_h.deleteItem(index);
        lf_h.deleteItem(index);
        assert(!f_h.findItem(index) && !lf_h.findItem(index));
    }

    return nullptr;
}

int main() 
{ 
  pthread_t threads[THREAD_COUNT];
  uint32_t threadNum[THREAD_COUNT];
  for(int i = 0; i < THREAD_COUNT; i++) {
    threadNum[i] = i;
    pthread_create(&threads[i], NULL, checkConsistency, (void *)&(threadNum[i]));
  }
  cout << "Hash Table behaves as it should.\n";
  for(int i = 0; i < THREAD_COUNT; i++)
    pthread_join(threads[i], NULL);
  
  return 0; 
}