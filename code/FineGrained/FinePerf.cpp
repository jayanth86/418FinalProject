#include "FineHashTable.h"
#include <cassert>
#include <pthread.h>
#include <queue>
#include <cmath>
#include <unistd.h>
#include "../CycleTimer.h"

int OPS = 1000000;
float INSERT = 0.33;
float DELETE = 0.33;
float SEARCH = 0.34;
int BUCKETS = 100;
int LOAD = 5;
int THREADS = 4;
int KEY_RANGE;
int DEBUG = 0;

FineHashTable *hashTable;

// Checks if the hash table has the values it should at any given point
void *checkConsistency(void *threadNumber) {
    int32_t threadNum = *((int32_t *)threadNumber);
    for(int32_t index = threadNum; index < OPS; index += THREADS) {
        hashTable->insertItem(index, 0);
        bool result = hashTable->findItem(index) != NULL;
        assert(result);
    }
    
    for(int32_t index = threadNum; index < OPS; index += THREADS) {
        hashTable->deleteItem(index);
        assert(!hashTable->findItem(index));
    }

    return nullptr;
}

static inline int generateKey(int l, int u) {
  int range = u - l;
  int offset = ceil(range * (rand() / float(RAND_MAX)));
  return l + offset;
}

void initHashTable(FineHashTable *hashTable) {
  for (int i = 0;  i < KEY_RANGE / 2; i++) {
    hashTable->insertItem(i, 0);
  }
}

void *performOps(void *arg) {
  queue<int> keyQueue;
  int threadId = *(int *)arg;
  srand(threadId);
  int l = threadId * (KEY_RANGE / THREADS);
  int u = (threadId + 1) * (KEY_RANGE / THREADS) - 1;
  for (int i = 0; i < OPS; i++) {
    float prob = rand() / (float)RAND_MAX;
    if (prob <= INSERT) {
      int key = generateKey(l, u);
      keyQueue.push(key);
      hashTable->insertItem(key, 0);
    }
    else if (prob <= (INSERT + DELETE)) {
      if (!keyQueue.empty()) {
        int key = keyQueue.front();
        keyQueue.pop();
        hashTable->deleteItem(key);
      }
    }
    else {
      int key = generateKey(l, u);
      hashTable->findItem(key);
    }
  }

  return nullptr;
}

int main(int argc, char *argv[]) 
{ 
  int opt;
  while ((opt = getopt(argc, argv, "o:i:d:b:l:t:c:")) != -1) {
    switch (opt) {
      case 'o':
        OPS = atoi(optarg);
        break;
      case 'i':
        INSERT = atof(optarg);
        break;
      case 'd':
        DELETE = atof(optarg);
        break;
      case 'b':
        BUCKETS = atoi(optarg);
        break;
      case 'l':
        LOAD = atoi(optarg);
        break;
      case 't':
        THREADS = atoi(optarg);
        break;
      case 'c':
        DEBUG = atoi(optarg);
        break;
      default:
        cerr << "Invalid argument " << optarg << endl;
    }
  }

  if (DELETE > INSERT) {
    cerr << "Delete ratio should be less than or equal to insert ratio" << endl;
    return 1;
  }
  SEARCH = 1 - INSERT - DELETE;
  KEY_RANGE = 2 * LOAD * BUCKETS;

  hashTable = new FineHashTable(BUCKETS);

  pthread_t threads[THREADS];
  uint32_t threadNum[THREADS];

  /* Correctness check */
  if (DEBUG) {
    for(int i = 0; i < THREADS; i++) {
      threadNum[i] = i;
      pthread_create(&threads[i], NULL, checkConsistency, (void *)&(threadNum[i]));
    }

    for(int i = 0; i < THREADS; i++)
      pthread_join(threads[i], NULL);

    cout << "Hash Table behaves as it should.\n";
  }

  /* Performance */
  initHashTable(hashTable);

  /* Start timer */
  double startTime =  CycleTimer::currentSeconds();
  for(int i = 0; i < THREADS; i++) {
    threadNum[i] = i;
    pthread_create(&threads[i], NULL, performOps, (void *)&(threadNum[i]));
  }

  for(int i = 0; i < THREADS; i++)
    pthread_join(threads[i], NULL);
  /* Stop timer */
  double endTime =  CycleTimer::currentSeconds();
  cout << "Execution time: " << endTime - startTime << " seconds" << endl;;
  return 0; 
}

/* Experiments:-
 * 1. Variation of load factor
 * 2. Variation of number of threads
 * 3. Variation of ops ratio
 */