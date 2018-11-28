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
    Node *node = table[index].findNode(key);
    if (node == NULL)
        table[index].insertNode(key, value);  
    else 
        node->value = value;
} 

bool HashTable::findItem(int key)
{
    int index = hashFunction(key); 
    return table[index].findNode(key) != NULL;
}

void HashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    table[index].deleteNode(key);
} 
  
// function to display hash table 
void HashTable::displayHash() { 
    for (int i = 0; i < NUM_BUCKETS; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
}
