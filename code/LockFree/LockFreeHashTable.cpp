#include "LockFreeHashTable.h"

using namespace std;

LockFreeHashTable::LockFreeHashTable(int NUM_BUCKETS)
{ 
    this->NUM_BUCKETS = NUM_BUCKETS;
    table = new LockFreeList[NUM_BUCKETS]; 
}

LockFreeHashTable::~LockFreeHashTable() {
    delete [] table;
}
  
void LockFreeHashTable::insertItem(int key, int value)
{ 
    int index = hashFunction(key);
    /* Need to handle 'key already in list' case */
    table[index].insertNode(key, value);
} 

bool LockFreeHashTable::findItem(int key)
{
    int index = hashFunction(key);
    return (table[index].findNode(key) != NULL);
}

void LockFreeHashTable::deleteItem(int key) 
{ 
    int index = hashFunction(key);  
    table[index].deleteNode(key);
} 
  
// function to display hash table 
void LockFreeHashTable::dispHashTable() { 
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
}
