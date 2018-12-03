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
    int result = _xbegin();
    if(result == _XBEGIN_STARTED) {
        if(table[index].lockingFlag) {
           _xabort(0xff);
        }
        if(!table[index].findNode(key))
            table[index].insertNode(key);
        _xend();
    }
    else {
        (table[index].m).lock();
        table[index].lockingFlag = true;
        if(!table[index].findNode(key))
            table[index].insertNode(key);  
        table[index].lockingFlag = false;
        (table[index].m).unlock();
    }
} 

bool STMHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    bool retval;
    int result = _xbegin();
    if(result == _XBEGIN_STARTED) {
        if(table[index].lockingFlag) {
            _xabort(0xff);
        }
        retval = table[index].findNode(key);
        _xend();
    }
    else {
        (table[index].m).lock();
        table[index].lockingFlag = true;
        retval = table[index].findNode(key);
        table[index].lockingFlag = false;
        (table[index].m).unlock();
    }
    return retval;
}

void STMHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    int result = _xbegin();
    if(result ==  _XBEGIN_STARTED) {
        if(table[index].lockingFlag) {
            _xabort(0xff);
        }
        table[index].deleteNode(key);
        _xend();
    }
    else {
        (table[index].m).lock();
        table[index].lockingFlag = true;
        table[index].deleteNode(key);
        table[index].lockingFlag = false;
        (table[index].m).unlock();
    }
} 
  
// function to display hash table 
void STMHashTable::displayHash() { 
    for (int index = 0; i < BUCKET; i++) { 
        cout << i;
        (table[index].m).lock();
        table[index].lockingFlag = true;
        table[index].dispList();
        table[index].lockingFlag = false;
        (table[index].m).unlock();
        cout << endl; 
    } 
}
