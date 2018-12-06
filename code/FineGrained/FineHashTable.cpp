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

int *FineHashTable::findItem(int key)
{   
    
    int index = hashFunction(key); 
    (table[index].m).lock();
    FineNode *retNode = table[index].findNode(key);
    (table[index].m).unlock();
    int *retVal = nullptr;
    if(retNode != nullptr)
        retVal = &(retNode->value);
    return retVal;
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
