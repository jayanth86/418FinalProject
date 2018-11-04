#include <iostream>

class Node {
	private:
		int key;
		Node *next;
	public:
		Node(int key);
		int getKey();
		Node *getNext();
		void setNext(Node *next);
};

class List {
	private:
		Node *head;
	public:
		List();
		~List();
		void insertNode(int key);
		void deleteNode(int key);
		Node *findNode(int key);
		void dispList();
};