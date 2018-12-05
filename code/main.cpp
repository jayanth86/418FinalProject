#include "Sequential/HashTable.h"
#include "FineGrained/FineHashTable.h"
#include "LockFree/LockFreeHashTable.h"
#include "STM/STMHashTable.h"
#include <cassert>
#include <pthread.h>
#define THREAD_COUNT 4
#define BUCKET_COUNT 50
#define ITER_COUNT 10000
FineHashTable f_h(BUCKET_COUNT);
LockFreeHashTable lf_h(BUCKET_COUNT);
STMHashTable rtm_h(BUCKET_COUNT);

// Checks if the hash table has the values it should at any given point
void *checkConsistency(void *threadNumber) {
    int32_t threadNum = *((int32_t *)threadNumber);
    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        f_h.insertItem(index, 0);
        lf_h.insertItem(index, 0);
        rtm_h.insertItem(index, 0);
        bool f_result = (f_h.findItem(index) && *(f_h.findItem(index)) == 0);
        bool lf_result = lf_h.findItem(index);
        bool rtm_result = (rtm_h.findItem(index) && *(rtm_h.findItem(index)) == 0);
        assert(f_result && lf_result && rtm_result);
    }
    
    for(int32_t index = threadNum; index < ITER_COUNT; index+=THREAD_COUNT) {
        f_h.deleteItem(index);
        lf_h.deleteItem(index);
        rtm_h.deleteItem(index);
        assert(!f_h.findItem(index) && !lf_h.findItem(index) && !rtm_h.findItem(index));
    }

    return nullptr;
}

int main(int argc, char *argv[]) 
{ 
  pthread_t threads[THREAD_COUNT];
  uint32_t threadNum[THREAD_COUNT];
  for(int i = 0; i < THREAD_COUNT; i++) {
    threadNum[i] = i;
    pthread_create(&threads[i], NULL, checkConsistency, (void *)&(threadNum[i]));
  }
  for(int i = 0; i < THREAD_COUNT; i++)
    pthread_join(threads[i], NULL);
  cout << "Hash Table behaves as it should.\n";
  return 0; 
}

/* Experiments:-
 * 1. Variation of load factor
 * 2. Variation of number of threads
 * 3. Variation of ops ratio
 */