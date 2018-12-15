#include "HashTable.h"

using namespace std;

HashTable::HashTable(int NUM_BUCKETS) 
{ 
    this->NUM_BUCKETS = NUM_BUCKETS; 
    table = new List[NUM_BUCKETS]; 
} 

HashTable::~HashTable() {
    delete [] table;
}
  
void HashTable::insertItem(int key, int value) 
{ 
    int index = hashFunction(key);
    this->m.lock();
    Node *node = table[index].findNode(key);
    if (node == NULL)
        table[index].insertNode(key, value);  
    else 
        node->value = value;
    this->m.unlock();
} 

int *HashTable::findItem(int key)
{
    int index = hashFunction(key); 
    this->m.lock();
    Node *retNode = table[index].findNode(key);
    int *retVal = NULL;
    if (retNode != NULL) {
        retVal = &(retNode->value);
    }
    this->m.unlock();
    return retVal;
}

void HashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    this->m.lock();
    table[index].deleteNode(key);
    this->m.unlock();
} 
  
// function to display hash table 
void HashTable::displayHash() { 
    this->m.lock();
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
    this->m.unlock();
}
