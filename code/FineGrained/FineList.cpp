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
	newNode->setNext(head);
	head = newNode;
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

bool FineList::findNode(int key) {
	FineNode *curr = head;
	while (curr != nullptr && curr->getKey() != key) {
		curr = curr->getNext();
	}
	return curr != nullptr;
}


void FineList::dispList() {
	FineNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}
