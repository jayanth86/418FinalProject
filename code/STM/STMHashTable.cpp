#include "STMHashTable.h"

using namespace std;

STMHashTable::STMHashTable(int b) 
{ 
    this->BUCKET = b; 
    table = new STMList[BUCKET]; 
} 
  
void STMHashTable::insertItem(int key) 
{ 
    int index = hashFunction(key);
    bool tm_flag = false;
    __transaction_atomic {
        if(!table[index].findNode(key))
            table[index].insertNode(key);

        if(table[index].findNode(key)) {
            tm_flag = true;
        }
        else {
            __transaction_cancel;
        }
    }
    if (!tm_flag) {
        (table[index].m).lock();
        if(!table[index].findNode(key))
            table[index].insertNode(key);  
        (table[index].m).unlock();
    } 
} 

bool STMHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    bool retval;
    __transaction_atomic {
        retval = table[index].findNode(key);
    }
    return retval;
}

void STMHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    __transaction_atomic {
        table[index].deleteNode(key);
    }
} 
  
// function to display hash table 
void STMHashTable::displayHash() { 
    for (int i = 0; i < BUCKET; i++) { 
        cout << i;
        __transaction_atomic {
            table[i].dispList();
        }
        cout << endl; 
    } 
}
