#include "HashTable.h"

using namespace std;

HashTable::HashTable(int b) 
{ 
    this->BUCKET = b; 
    table = new List[BUCKET]; 
} 
  
void HashTable::insertItem(int key) 
{ 
    int index = hashFunction(key); 
    table[index].insertNode(key);  
} 
  
void HashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
  
    table[index].deleteNode(key);
} 
  
// function to display hash table 
void HashTable::displayHash() { 
    for (int i = 0; i < BUCKET; i++) { 
        cout << i; 
        table[i].dispList();
        cout << endl; 
    } 
}
