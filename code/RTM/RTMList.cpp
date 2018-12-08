#include "RTMList.h"

using namespace std;

RTMNode::RTMNode(int key, int val) {
	this->key = key;
	this->val = val;
	this->next = NULL;
}

int RTMNode::getKey() {
	return this->key;
}

int RTMNode::getVal() {
	return this->val;
}

RTMNode *RTMNode::getNext() {
	return this->next;
}

void RTMNode::setNext(RTMNode *next) {
	this->next = next;
}

void RTMNode::setVal(int val) {
	this->val = val;
}

RTMList::RTMList() {
	this->head = NULL;
	this->lockingFlag = false;
}

RTMList::~RTMList() {
	RTMNode *curr = head;

	while (curr != NULL) {
		RTMNode *tmp = curr;
		curr = curr->getNext();
		delete tmp;
	}
}

void RTMList::insertNode(int key, int val) {
	RTMNode *newNode = new RTMNode(key, val);
	newNode->setNext(head);
	head = newNode;
}

void RTMList::deleteNode(int key) {

	RTMNode *prev = NULL;
	RTMNode *curr = head;

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

RTMNode *RTMList::findNode(int key) {
	RTMNode *curr = head;
	while (curr != nullptr && curr->getKey() != key) {
		curr = curr->getNext();
	}
	return curr;
}


void RTMList::dispList() {
	RTMNode *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}