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

int * LockFreeHashTable::findItem(int key)
{
    int index = hashFunction(key);
    LockFreeNode *retNode = table[index].findNode(key);
    int *retVal = NULL;
    if (retNode != NULL) {
        retVal = &(retNode->value);
    }
    return retVal;
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
