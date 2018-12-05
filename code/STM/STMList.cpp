#include "STMList.h"

using namespace std;

STMNode::STMNode(int key, int val) {
	this->key = key;
	this->val = val;
	this->next = NULL;
}

int STMNode::getKey() {
	return this->key;
}

int STMNode::getVal() {
	return this->val;
}

STMNode *STMNode::getNext() {
	return this->next;
}

void STMNode::setNext(STMNode *next) {
	this->next = next;
}

void STMNode::setVal(int val) {
	this->val = val;
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

void STMList::insertNode(int key, int val) {
	STMNode *newNode = new STMNode(key, val);
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

STMNode *STMList::findNode(int key) {
	STMNode *curr = head;
	while (curr != nullptr && curr->getKey() != key) {
		curr = curr->getNext();
	}
	return curr;
}


void STMList::dispList() {
	STMNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}
