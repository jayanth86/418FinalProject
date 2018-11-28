#include <iostream>
#include <mutex>
using namespace std;

class FineNode {
	public:
		int key;
		int value;
		FineNode *next;
		FineNode(int key, int value);
		int getKey();
		FineNode *getNext();
		void setNext(FineNode *next);
};

class FineList {
	public:
		FineNode *head;
		mutable mutex m;
		FineList();
		~FineList();
		void insertNode(int key, int value);
		void deleteNode(int key);
		FineNode * findNode(int key);
		void dispList();
};