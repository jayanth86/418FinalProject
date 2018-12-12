#include "List.h"
#include <mutex>
using namespace std;

class HashTable 
{ 
    int NUM_BUCKETS;    // No. of buckets 
  
    // Pointer to an array containing buckets 
    List *table;
    mutable mutex m;
public: 
    HashTable(int V);  // Constructor 

    ~HashTable(); // Destructor 
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



