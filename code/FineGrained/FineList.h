#include <iostream>
#include <shared_timed_mutex>
using namespace std;

class FineNode {
	private:
		int key;
		FineNode *next;
	public:
		mutable shared_timed_mutex m;
		FineNode(int key);
		int getKey();
		FineNode *getNext();
		void setNext(FineNode *next);
};

class FineList {
	private:
		FineNode *head;
		mutable shared_timed_mutex m;
	public:
		FineList();
		~FineList();
		void insertNode(int key);
		void deleteNode(int key);
		bool findNode(int key);
		void dispList();
};