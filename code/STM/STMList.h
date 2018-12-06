#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;

class STMNode {
	public:
		int key;
		int val;
		STMNode *next;
		STMNode(int key, int val);
		int getKey();
		int getVal();
		void setVal(int val);
		STMNode *getNext();
		void setNext(STMNode *next);
};

class STMList {
	private:
		STMNode *head;
	public:
		mutable mutex m;
		atomic<bool> lockingFlag;
		STMList();
		~STMList();
		void insertNode(int key, int val);
		void deleteNode(int key);
		STMNode *findNode(int key);
		void dispList();
};