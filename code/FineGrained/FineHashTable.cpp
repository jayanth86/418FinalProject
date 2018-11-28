#include "FineHashTable.h"

using namespace std;

FineHashTable::FineHashTable(int NUM_BUCKETS) 
{ 
    this->NUM_BUCKETS = NUM_BUCKETS; 
    table = new FineList[NUM_BUCKETS]; 
} 

FineHashTable::~FineHashTable() {
    delete [] table;
}
  
void FineHashTable::insertItem(int key, int value) 
{ 
    int index = hashFunction(key);
    (table[index].m).lock();
    FineNode *node = table[index].findNode(key);
    if (node == NULL)
        table[index].insertNode(key, value);  
    else 
        node->value = value;
    (table[index].m).unlock();
} 

bool FineHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    (table[index].m).lock();
    bool retval = table[index].findNode(key) != NULL;
    (table[index].m).unlock();
    return retval;
}

void FineHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    (table[index].m).lock();
    table[index].deleteNode(key);
    (table[index].m).unlock();
} 
  
// function to display hash table 
void FineHashTable::displayHash() { 
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        cout << i; 
        (table[i].m).lock();
        table[i].dispList();
        (table[i].m).unlock();
        cout << endl; 
    } 
}
