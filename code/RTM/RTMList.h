#include <iostream>
#include <mutex>
#include <atomic>
using namespace std;

class RTMNode {
	public:
		int key;
		int val;
		RTMNode *next;
		RTMNode(int key, int val);
		int getKey();
		int getVal();
		void setVal(int val);
		RTMNode *getNext();
		void setNext(RTMNode *next);
};

class RTMList {
	private:
		RTMNode *head;
	public:
		mutable mutex m;
		atomic<bool> lockingFlag;
		RTMList();
		~RTMList();
		void insertNode(int key, int val);
		void deleteNode(int key);
		RTMNode *findNode(int key);
		void dispList();
};