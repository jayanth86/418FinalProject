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
    (table[index].m).lock();
    if(!table[index].findNode(key))
        table[index].insertNode(key);  
    (table[index].m).unlock();
} 

bool FineHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    (table[index].m).lock();
    bool retval = table[index].findNode(key);
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
    for (int i = 0; i < BUCKET; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
}
