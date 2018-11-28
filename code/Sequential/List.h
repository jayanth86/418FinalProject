#include <iostream>

class Node {
	public:
		int key;
		int value;
		Node *next;
		Node(int key, int value);
};

class List {
	private:
		Node *head;
	public:
		List();
		~List();
		void insertNode(int key, int value);
		void deleteNode(int key);
		Node *findNode(int key);
		void dispList();
};