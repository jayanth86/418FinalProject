#include "List.h"

using namespace std;

Node::Node(int key) {
	this->key = key;
	this->next = NULL;
}

int Node::getKey() {
	return this->key;
}

Node * Node::getNext() {
	return this->next;
}

void Node::setNext(Node *next) {
	this->next = next;
}

List::List() {
	this->head = NULL;
}

List::~List() {
	Node *curr = head;

	while (curr != NULL) {
		Node *tmp = curr;
		curr = curr->getNext();
		delete tmp;
	}
}

void List::insertNode(int key) {

	Node *newNode = new Node(key);
	newNode->setNext(head);
	head = newNode;
}

void List::deleteNode(int key) {

	Node *prev = NULL;
	Node *curr = head;

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

Node *List::findNode(int key) {

	Node *curr = head;

	while (curr != NULL && curr->getKey() != key) {
		curr = curr->getNext();
	}

	return curr;
}


void List::dispList() {

	Node *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->getKey(); 
		curr = curr->getNext();
	}
}
