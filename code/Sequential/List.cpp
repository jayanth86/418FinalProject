#include "List.h"

using namespace std;

Node::Node(int key, int value) {
	this->key = key;
	this->value = value;
	this->next = NULL;
}

List::List() {
	this->head = NULL;
}

List::~List() {
	Node *curr = head;

	while (curr != NULL) {
		Node *tmp = curr;
		curr = curr->next;
		delete tmp;
	}
}

void List::insertNode(int key, int value) {

	Node *newNode = new Node(key, value);
	newNode->next = head;
	head = newNode;
}

void List::deleteNode(int key) {

	Node *prev = NULL;
	Node *curr = head;

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

Node *List::findNode(int key) {

	Node *curr = head;

	while (curr != NULL && curr->key != key) {
		curr = curr->next;
	}

	return curr;
}


void List::dispList() {

	Node *curr = head;
	while (curr != NULL) {
		cout << " --> " << curr->key; 
		curr = curr->next;
	}
}
