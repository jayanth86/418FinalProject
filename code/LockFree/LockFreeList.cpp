#include "LockFreeList.h"
#include <limits.h>
using namespace std;

LockFreeNode::LockFreeNode(int key, int value) {
    this->key = key;
    this->value = value;
    this->succ = NULL;
}

bool extractMark(LockFreeNode *node) {
    return (unsigned long)node & 2;
}

bool extractFlag(LockFreeNode *node) {
    return (unsigned long)node & 1;
}

static inline LockFreeNode *extractNext(LockFreeNode *node) {
    return (LockFreeNode *)((unsigned long)node & ~3);
}

bool LockFreeNode::getMark() {
    return extractMark(this->succ);
}

bool LockFreeNode::getFlag() {
    return extractFlag(this->succ);   
}

LockFreeNode *LockFreeNode::getNext() {
    return extractNext(this->succ);
}

LockFreeNode *packSucc(LockFreeNode *node, bool mark, bool flag) {
    return (LockFreeNode *)((unsigned long)node | (mark << 1) | flag);
}

LockFreeList::LockFreeList() {
    this->head = new LockFreeNode(INT_MIN, 0);
    this->tail = new LockFreeNode(INT_MAX, 0);
    head->succ = packSucc(this->tail, 0, 0);
    tail->succ = packSucc(NULL, 0, 0);
}

LockFreeList::~LockFreeList() {
    LockFreeNode *curr = head;

    while (curr != NULL) {
        LockFreeNode *tmp = curr;
        curr = curr->getNext();
        delete tmp;
    }
}

LockFreeNode *LockFreeList::searchNode(int key) {
    node_pair_t nodePair = searchFrom(key, head);
    LockFreeNode *currNode = nodePair.first;
    if(currNode->key == key) {
        return currNode;
    }
    else {
        return NULL;
    }
}

node_pair_t LockFreeList::searchFrom(float key, LockFreeNode *currNode) {
    LockFreeNode *nextNode = currNode->getNext();
    while (nextNode->key <= key) {
        while (nextNode->getMark() == 1 && 
               (currNode->getMark() == 0 || currNode->getNext() != nextNode)) {
            if (currNode->getNext() == nextNode) {
                helpMarked(currNode, nextNode);
            }
            nextNode = currNode->getNext();
        }
        if (nextNode->key <= key) {
            currNode = nextNode;
            nextNode = currNode->getNext();
        }
    }
    return make_pair(currNode, nextNode);
}

void LockFreeList::helpMarked(LockFreeNode *prevNode, LockFreeNode *delNode) {

    LockFreeNode *nextNode = delNode->getNext();
    LockFreeNode *succOld = packSucc(delNode, 0, 1);
    LockFreeNode *succNew = packSucc(nextNode, 0, 0);
    __sync_bool_compare_and_swap(&(prevNode->succ), succOld, succNew);
}

LockFreeNode *LockFreeList::deleteNode(int key) {
    node_pair_t nodePair = searchFrom(key - 0.1, head);
    LockFreeNode *prevNode = nodePair.first;
    LockFreeNode *delNode = nodePair.second;
    if (delNode->key != key) {
        return NULL;
    }

    node_bool_pair_t nodeBoolPair = tryFlag(prevNode, delNode);
    prevNode = nodeBoolPair.first;
    bool result = nodeBoolPair.second;

    if (prevNode != NULL) {
        helpFlagged(prevNode, delNode);
    }
    if (result == false) {
        return NULL;
    }
    return delNode;
}

void LockFreeList::helpFlagged(LockFreeNode *prevNode, LockFreeNode *delNode) {
    delNode->backLink = prevNode;
    if (delNode->getMark() == 0) {
        tryMark(delNode);
    }
    helpMarked(prevNode, delNode);
}

void LockFreeList::tryMark(LockFreeNode *delNode) {
    while (delNode->getMark() != 1) {
        LockFreeNode *nextNode = delNode->getNext();
        LockFreeNode *succOld = packSucc(nextNode, 0, 0);
        LockFreeNode *succNew = packSucc(nextNode, 1, 0);
        LockFreeNode *result = __sync_val_compare_and_swap(&(delNode->succ), succOld, succNew);
        if (extractMark(result) == 0 && extractFlag(result) == 1) {
            helpFlagged(delNode, extractNext(result));
        }
    }
}

node_bool_pair_t LockFreeList::tryFlag(LockFreeNode *prevNode, LockFreeNode *targetNode) {
    while (true) {

        if (prevNode->succ == packSucc(targetNode, 0, 1)) {
            return make_pair(prevNode, false);
        }

        LockFreeNode *succOld = packSucc(targetNode, 0, 0);
        LockFreeNode *succNew = packSucc(targetNode, 0, 1);

        LockFreeNode *result = __sync_val_compare_and_swap(&(prevNode->succ), succOld, succNew);
        if (result == succOld) {
            return make_pair(prevNode, true);
        }
        if (result == succNew) {
            return make_pair(prevNode, false);
        }
        while (prevNode->getMark() == 1) {
            prevNode = prevNode->backLink;
        }
        node_pair_t nodePair = searchFrom(targetNode->key - 0.1, prevNode);
        LockFreeNode *delNode = nodePair.second;
        if (delNode != targetNode) {
            return make_pair((LockFreeNode *)NULL, false);
        }
    }
}

LockFreeNode *LockFreeList::insertNode(int key, int value) {

    node_pair_t nodePair = searchFrom(key, head);
    LockFreeNode *prevNode = nodePair.first;
    LockFreeNode *nextNode = nodePair.second;
    
    /* modify to replace value if key is duplicate. returning NULL for now */
    if (prevNode->key == key) {
        return  NULL;
    }
    LockFreeNode *newNode = new LockFreeNode(key, value);
    while (true) {
        if(prevNode->getFlag() == 1) {
            helpFlagged(prevNode, prevNode->getNext());
        }
        else {
            newNode->succ = packSucc(nextNode, 0, 0);
            LockFreeNode *succOld = packSucc(nextNode, 0, 0);
            LockFreeNode *succNew = packSucc(newNode, 0, 0);

            LockFreeNode *result = __sync_val_compare_and_swap(&(prevNode->succ), succOld, succNew);

            if (result == succOld) {
                return newNode;
            }
            else {
                if (extractMark(result) == 0 && extractFlag(result) == 1) {
                    helpFlagged(prevNode, extractNext(result));
                }
                while (prevNode->getMark() == 1) {
                    prevNode = prevNode->backLink;
                }
            }
        }
        nodePair = searchFrom(key, prevNode);
        if (prevNode->key == key) {
            delete newNode;
            /* modify to replace value if key is duplicate. returning NULL for now */
            return NULL;
        }
    }
}

void LockFreeList::dispList() {

    LockFreeNode *curr = head->getNext();
    if (curr == tail) {
        cout << " LIST EMPTY";
        return;
    }
    cout << " HEAD";
    while (curr != tail) {
        cout << " --> (" << curr->key << ", " << curr->value << ")" ; 
        curr = curr->getNext();
    }
    cout << " --> TAIL" << endl;
}


/* Things to do:-
 * 1. modify logic in insertNode for duplicate key
 */