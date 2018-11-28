#include <iostream>
#include <utility>
#include <atomic>

using namespace std;

class LockFreeNode;

typedef pair<LockFreeNode *, LockFreeNode *> node_pair_t;
typedef pair<LockFreeNode *, bool> node_bool_pair_t;

class LockFreeNode {
	public:
		int key;
		int value;
		LockFreeNode *succ;
		LockFreeNode *backLink;

		LockFreeNode(int key, int value);
		bool getMark();
		bool getFlag();
		LockFreeNode *getNext();
		LockFreeNode *packSucc(LockFreeNode *node, bool mark, bool flag);
};

class LockFreeList {
	public:
		LockFreeNode *head;
		LockFreeNode *tail;
		LockFreeList();
		~LockFreeList();
		LockFreeNode *insertNode(int key, int value);
		LockFreeNode *deleteNode(int key);
		LockFreeNode *findNode(int key);
		node_pair_t searchFrom(float key, LockFreeNode *currNode);
		void helpMarked(LockFreeNode *prevNode, LockFreeNode *delNode);
		void helpFlagged(LockFreeNode *prevNode, LockFreeNode *delNode);
		void tryMark(LockFreeNode *delNode);
		node_bool_pair_t tryFlag(LockFreeNode *prevNode, LockFreeNode *targetNode);
		void dispList();
};