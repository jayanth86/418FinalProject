#include "RTMHashTable.h"

using namespace std;

RTMHashTable::RTMHashTable(int b) 
{ 
    this->BUCKET = b; 
    table = new RTMList[BUCKET]; 
} 
  
void RTMHashTable::insertItem(int key, int val) 
{ 
    int index = hashFunction(key);
    unsigned result = _xbegin();
    RTMNode *nd;
    if(result == _XBEGIN_STARTED) {
        if(table[index].lockingFlag) {
           _xabort(0xff);
        }
        if((nd = table[index].findNode(key)) == nullptr)
            table[index].insertNode(key, val);
        else 
            nd->setVal(val);
        _xend();
    }
    else {
        (table[index].m).lock();
        table[index].lockingFlag = true;
        if((nd = table[index].findNode(key)) == nullptr)
            table[index].insertNode(key, val); 
        else 
            nd->setVal(val);
        table[index].lockingFlag = false;
        (table[index].m).unlock();
    }
} 

int *RTMHashTable::findItem(int key)
{
    int index = hashFunction(key); 
    RTMNode *retNode;
    unsigned result = _xbegin();
    if(result == _XBEGIN_STARTED) {
        if(table[index].lockingFlag) {
            _xabort(0xff);
        }
        retNode = table[index].findNode(key);
        _xend();
    }
    else {
        (table[index].m).lock();
        table[index].lockingFlag = true;
        retNode = table[index].findNode(key);
        table[index].lockingFlag = false;
        (table[index].m).unlock();
    }
    int *retVal = nullptr;
    if(retNode != nullptr) 
        retVal = &(retNode->val);
    return retVal;
}

void RTMHashTable::deleteItem(int key) 
{ 
    // get the hash index of key 
    int index = hashFunction(key); 
    unsigned result = _xbegin();
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
void RTMHashTable::displayHash() { 
    for (int index = 0; index < BUCKET; index++) { 
        cout << index;
        (table[index].m).lock();
        table[index].lockingFlag = true;
        table[index].dispList();
        table[index].lockingFlag = false;
        (table[index].m).unlock();
        cout << endl; 
    } 
}