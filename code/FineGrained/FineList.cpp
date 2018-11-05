#include "FineList.h"

using namespace std;

FineNode::FineNode(int key) {
	this->key = key;
	this->next = NULL;
}

int FineNode::getKey() {
	return this->key;
}

FineNode * FineNode::getNext() {
	return this->next;
}

void FineNode::setNext(FineNode *next) {
	this->next = next;
}

FineList::FineList() {
	this->head = NULL;
}

FineList::~FineList() {
	FineNode *curr = head;

	while (curr != NULL) {
		FineNode *tmp = curr;
		curr = curr->getNext();
		delete tmp;
	}
}

void FineList::insertNode(int key) {
	FineNode *newNode = new FineNode(key);
	(newNode->m).lock();
	newNode->setNext(head);
	(newNode->m).unlock();
	(this->m).lock();
	head = newNode;
	(this->m).unlock();
}

void FineList::deleteNode(int key) {

	FineNode *prev = NULL;
	FineNode *curr = head;

	while (curr != NULL && curr->getKey() != key) {
		prev = curr;
		curr = curr->getNext();
	}

	if (curr != NULL) {
		if (prev != NULL) {
			prev->setNext(curr->getNext());
		}
		else {
			head = curr->getNext();
		}
		delete curr;
	}
}

boolFineList::findNode(int key) {
	(this->m).lock_shared();
	FineNode *curr = head;
	bool listLock = true;
	while (curr != NULL && curr->getKey() != key) {
		if(listLock) {
			(this->m).unlock_shared();
			listLock = false;
		}
		curr = curr->getNext();
	}
	if(listLock) {
			(this->m).unlock_shared();
			listLock = false;
	}
	return curr;
}


void FineList::dispList() {

	FineNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}
