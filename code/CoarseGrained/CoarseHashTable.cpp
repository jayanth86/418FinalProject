#include "CoarseHashTable.h"

using namespace std;

CoarseHashTable::CoarseHashTable(int NUM_BUCKETS) 
{ 
    this->NUM_BUCKETS = NUM_BUCKETS; 
    table = new CoarseList[NUM_BUCKETS]; 
} 

CoarseHashTable::~CoarseHashTable() {
    delete [] table;
}
  
void CoarseHashTable::insertItem(int key, int value) 
{ 
    int index = hashFunction(key);
    m.lock();
    CoarseNode *node = table[index].findNode(key);
    if (node == NULL)
        table[index].insertNode(key, value);  
    else 
        node->value = value;
    m.unlock();
} 

int *CoarseHashTable::findItem(int key)
{   
    
    int index = hashFunction(key); 
    m.lock();
    CoarseNode *retNode = table[index].findNode(key);
    m.unlock();
    int *retVal = nullptr;
    if(retNode != nullptr)
        retVal = &(retNode->value);
    return retVal;
}

void CoarseHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    m.lock();
    table[index].deleteNode(key);
    m.unlock();
} 
  
// function to display hash table 
void CoarseHashTable::displayHash() { 
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        cout << i;
        m.lock();
        table[i].dispList();
        m.unlock();
        cout << endl; 
    } 
}
