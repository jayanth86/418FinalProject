#include "LockFreeHashTable.h"

#define NUM_BUCKTETS 10
int main() {
	LockFreeHashTable *hashTable = new LockFreeHashTable(NUM_BUCKTETS);
	hashTable->insertItem(0, 10);
	// hashTable->insertItem(10, 10);
	// hashTable->dispHashTable();
	// hashTable->insertItem(1, 11);
	// hashTable->dispHashTable();
	// hashTable->deleteItem(1);
	// hashTable->dispHashTable();
	// hashTable->deleteItem(2);
	// hashTable->dispHashTable();
	// hashTable->insertItem(0, 9);
	// hashTable->dispHashTable();
	return 0;
}