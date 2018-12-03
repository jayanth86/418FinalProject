#include <iostream>
#include <mutex>
using namespace std;

class STMNode {
	private:
		int key;
		STMNode *next;
	public:
		STMNode(int key);
		int getKey();
		STMNode *getNext();
		void setNext(STMNode *next);
};

class STMList {
	private:
		STMNode *head;
	public:
		mutable mutex m;
		bool lockingFlag;
		STMList();
		~STMList();
		void insertNode(int key);
		void deleteNode(int key);
		bool findNode(int key);
		void dispList();
};