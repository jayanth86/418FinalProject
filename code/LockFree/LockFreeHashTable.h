#include "LockFreeList.h"
using namespace std;

class LockFreeHashTable 
{ 
    int NUM_BUCKETS;
    LockFreeList *table;

public: 
    LockFreeHashTable(int NUM_BUCKETS);

    ~LockFreeHashTable();

    // inserts a (key, value) pair into hash table 
    void insertItem(int key, int value); 
    
    // deletes a (key, value) pair from hash table 
    void deleteItem(int key); 

    // finds a (key, value) pair in hash table
    LockFreeNode *findItem(int key);
  
    // hash function to map values to key 
    int hashFunction(int key) { 
        return (key % NUM_BUCKETS); 
    } 
  
    void dispHashTable(); 
}; 



