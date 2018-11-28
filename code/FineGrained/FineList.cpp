#include "FineList.h"

using namespace std;

FineNode::FineNode(int key, int value) {
	this->key = key;
	this->value = value;
	this->next = NULL;
}

FineList::FineList() {
	this->head = NULL;
}

FineList::~FineList() {
	FineNode *curr = head;

	while (curr != NULL) {
		FineNode *tmp = curr;
		curr = curr->next;
		delete tmp;
	}
}

void FineList::insertNode(int key, int value) {
	FineNode *newNode = new FineNode(key, value);
	newNode->next = head;
	head = newNode;
}

void FineList::deleteNode(int key) {

	FineNode *prev = NULL;
	FineNode *curr = head;

	while (curr != NULL && curr->key != key) {
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL) {
		if (prev != NULL) {
			prev->next = curr->next;
		}
		else {
			head = curr->next;
		}
		delete curr;
	}
}

FineNode * FineList::findNode(int key) {
	FineNode *curr = head;
	while (curr != nullptr && curr->key != key) {
		curr = curr->next;
	}
	return curr;
}


void FineList::dispList() {
	FineNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->key; 
		curr = curr->next;
	}
}
