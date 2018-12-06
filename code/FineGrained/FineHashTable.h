#include "FineList.h"
using namespace std;

class FineHashTable 
{ 
    int NUM_BUCKETS;    // No. of buckets 
  
    // Pointer to an array containing buckets 
    FineList *table;
public: 
    FineHashTable(int NUM_BUCKETS);

    ~FineHashTable();
    // inserts a key into hash table 
    void insertItem(int key, int value); 
    
    // deletes a key from hash table 
    void deleteItem(int key); 

    // checks if key is in hash table
    int *findItem(int key);
  
    // hash function to map values to key 
    int hashFunction(int x) { 
        return (x % NUM_BUCKETS); 
    } 
  
    void displayHash(); 
}; 



