#include "LockFreeHashTable.h"

using namespace std;

LockFreeHashTable::LockFreeHashTable(int NUM_BUCKETS)
{ 
    this->NUM_BUCKETS = NUM_BUCKETS; 
    table = new LockFreeList[NUM_BUCKETS]; 
}

LockFreeHashTable::~LockFreeHashTable() {
    for (int i = 0; i < NUM_BUCKETS; i++) {
        delete &table[i];
    }
    delete table;
}
  
void LockFreeHashTable::insertItem(int key, int value)
{ 
    int index = hashFunction(key);
    table[index].insertNode(key, value);
} 

LockFreeNode *LockFreeHashTable::findItem(int key)
{
    int index = hashFunction(key);
    return table[index].searchNode(key);
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
