#include <iostream>

using namespace std;

class CoarseNode {
	public:
		int key;
		int value;
		CoarseNode *next;
		CoarseNode(int key, int value);
		int getKey();
		CoarseNode *getNext();
		void setNext(CoarseNode *next);
};

class CoarseList {
	public:
		CoarseNode *head;
		CoarseList();
		~CoarseList();
		void insertNode(int key, int value);
		void deleteNode(int key);
		CoarseNode * findNode(int key);
		void dispList();
};