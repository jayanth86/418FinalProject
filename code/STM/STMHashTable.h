#include "STMList.h"
#include "immintrin.h"
using namespace std;

class STMHashTable 
{ 
    int BUCKET;    // No. of buckets 
  
    // Pointer to an array containing buckets 
    STMList *table;
public: 
    STMHashTable(int V);  // Constructor 
    // inserts a key into hash table 
    void insertItem(int key, int val); 
    
    // deletes a key from hash table 
    void deleteItem(int key); 

    // checks if key is in hash table
    int *findItem(int key);
  
    // hash function to map values to key 
    int hashFunction(int x) { 
        return (x % BUCKET); 
    } 
  
    void displayHash(); 
}; 



