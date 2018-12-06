#include "Cycletimer.h"
#include "LockFreeHashTable.h"
#include <cassert>
#include <pthread.h>
#include <getopt.h>
#include <cstdlib>
#include <cmath>

using namespace std;

int OPS = 1000000;
float INSERT = 0.33;
float DELETE = 0.33;
float SEARCH = 0.34;
int BUCKETS = 100;
int LOAD = 5;
int THREADS = 4;
int KEY_RANGE = 2 * LOAD * BUCKETS;

static inline int generateKey(int l, int u) {
	int range = u - l;
	int offset = ceil(range * (rand() / float(RAND_MAX)));
	return l + offset;
}

void initHashTable(LockFreeHashTable *hashTable) {
	for (int i = 0;  i < KEY_RANGE / 2; i++) {
		hashTable->insertItem(i, 0);
	}
}

void performOps(void *arg) {

	int threadId = *(int *)arg;
	srand(threadId);
	for (int i = 0; i < OPS; i++) {
		


	}
}


int main(int argc, char *argv[]) {

	while (opt = getopt(argc, argv, "o::i::d::b::l::t::") != -1) {
		switch (opt) {
			case 'o':
				OPS = atoi(optarg);
				break;
			case 'i':
				INSERT = atof(optarg);
				break;
			case 'd':
				DELETE = atof(optarg);
				break;
			case 'b':
				BUCKETS = atoi(optarg);
				break;
			case 'l':
				LOAD = atoi(optarg);
				break;
			case 't':
				THREADS = atoi(optarg);
				break;
			case 'h':
				THREADS = atoi(optarg);
				break;
			default:
				cerr << "Invalid argument " << optarg << endl;
		}
	}
	if (DELETE > INSERT) {
		cerr << "Delete ratio should be less than or equal to insert ratio" << endl;
	}
	SEARCH = 1 - INSERT - DELETE;

	hashTable =  LockFreeHashTable(BUCKETS);
	initHashTable(hashTable);

	int threadIds[THREADS];
	pthread_t threadNum[THREADS];
	for (int i = 0; i < THREADS; i++) {
		threadIds[i] = i;
		pthread_create(&threadNum[i], NULL, performOps, &threadIds[i]);
	}
	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadNum[i], NULL);
	}

	return 0;
}
