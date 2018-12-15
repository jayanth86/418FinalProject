#include "CoarseList.h"

using namespace std;

CoarseNode::CoarseNode(int key, int value) {
	this->key = key;
	this->value = value;
	this->next = NULL;
}

CoarseList::CoarseList() {
	this->head = NULL;
}

CoarseList::~CoarseList() {
	CoarseNode *curr = head;

	while (curr != NULL) {
		CoarseNode *tmp = curr;
		curr = curr->next;
		delete tmp;
	}
}

void CoarseList::insertNode(int key, int value) {
	CoarseNode *newNode = new CoarseNode(key, value);
	newNode->next = head;
	head = newNode;
}

void CoarseList::deleteNode(int key) {

	CoarseNode *prev = NULL;
	CoarseNode *curr = head;

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

CoarseNode *CoarseList::findNode(int key) {
	CoarseNode *curr = head;
	while (curr != nullptr && curr->key != key) {
		curr = curr->next;
	}
	return curr;
}


void CoarseList::dispList() {
	CoarseNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->key; 
		curr = curr->next;
	}
}
