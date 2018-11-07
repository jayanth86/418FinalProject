#include <iostream>
#include <mutex>
using namespace std;

class FineNode {
	private:
		int key;
		FineNode *next;
	public:
		FineNode(int key);
		int getKey();
		FineNode *getNext();
		void setNext(FineNode *next);
};

class FineList {
	private:
		FineNode *head;
	public:
		mutable mutex m;
		FineList();
		~FineList();
		void insertNode(int key);
		void deleteNode(int key);
		bool findNode(int key);
		void dispList();
};