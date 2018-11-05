#include "FineHashTable.h"

using namespace std;

FineHashTable::FineHashTable(int b) 
{ 
    this->BUCKET = b; 
    table = new FineList[BUCKET]; 
} 
  
void FineHashTable::insertItem(int key) 
{ 
    int index = hashFunction(key);
    if(!table[index].findNode(key))
        table[index].insertNode(key);  
} 

bool FineHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    return table[index].findNode(key) != NULL;
}

void FineHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
  
    table[index].deleteNode(key);
} 
  
// function to display hash table 
void FineHashTable::displayHash() { 
    for (int i = 0; i < BUCKET; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
}
