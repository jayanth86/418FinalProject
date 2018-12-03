#include "STMList.h"

using namespace std;

STMNode::STMNode(int key) {
	this->key = key;
	this->next = NULL;
}

int STMNode::getKey() {
	return this->key;
}

STMNode * STMNode::getNext() {
	return this->next;
}

void STMNode::setNext(STMNode *next) {
	this->next = next;
}

STMList::STMList() {
	this->head = NULL;
	this->lockingFlag = false;
}

STMList::~STMList() {
	STMNode *curr = head;

	while (curr != NULL) {
		STMNode *tmp = curr;
		curr = curr->getNext();
		delete tmp;
	}
}

void STMList::insertNode(int key) {
	STMNode *newNode = new STMNode(key);
	newNode->setNext(head);
	head = newNode;
}

void STMList::deleteNode(int key) {

	STMNode *prev = NULL;
	STMNode *curr = head;

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

bool STMList::findNode(int key) {
	STMNode *curr = head;
	while (curr != nullptr && curr->getKey() != key) {
		curr = curr->getNext();
	}
	return curr != nullptr;
}


void STMList::dispList() {
	STMNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}
