## Summary
We implemented concurrent hash tables with multiple different implementations and compared their performance while tweaking various factors. We implemented a fine-grained hash table, coarse-grained hash table, lockless hash table, and a transactional hash table for use with a restricted transactional memory system. We then compared the performance of each different table while altering the number of threads, range of keys, and ratio of read and write operations. We observed that the lockless implementation is the best, while the coarse-grained hash table performs the worst out of the four. The transactional implementation also outperformed the fine-grained hash table implementation. 


## Background
The key data structure that we use here is a concurrent hash table with chaining for collisions. We don’t attempt to resize the hash table, since we were warned this approach would be too difficult to finish within the scope of our project. As previously mentioned, we have four implementations of concurrent hash tables here: coarse-grained locking, fine-grained locking, lockless, and transactional. Each implementation of the hash table must insert, delete, and find items.

Function signatures:

void HashTable::insertItem(int key, int value)

int *HashTable::findItem(int key)

void HashTable::deleteItem(int key)

insertItem takes a key-value pair and inserts the mapping from the provided key to the provided value into the hash table. findItem takes an input key and returns the value mapped to the key. deleteItem takes an input key and removes the mapping associated with the key from the table if it exists. 
Our performance testing algorithms take in inputs of number of operations, number of threads, range of keys mapped to each index/bucket, and the ratio of read to write operations. The output would be the time taken for the threads to perform all their operations and terminate. 

Hash tables are one of the most important concurrent data structures and have numerous use cases. Since reading and writing to a concurrent hash table can take up the majority of the time in many of these use cases, we attempt to implement and compare different implementations of concurrent hash tables. We are not trying to speedup the usage of a general hash table, but are instead hoping to allow multiple threads to read and write to the same set of data using a key-value store. This, in turn, would allow hash tables to be used as shared memory space for various applications that want to use parallelism to speedup their work. 

There are no real dependencies in the program and the amount of parallelism in the program is up to the user, since we don’t limit the number of threads used. We don’t make use of SIMD in any way and it is also not data-parallel. Locality also doesn’t play a large role in our data structure since chaining is implemented with a linked list instead of an unbounded array. 

## Platform:
For the purposes of this project, we tested all our code on Microsoft Azure’s Standard_E2s_v3 machines for consistency and restricted transactional memory support. These machines feature 2.3 GHz Intel XEON ® E5-2673 v4 chips, with support for hyper-threading technology. We chose these machines specifically due to their easy availability and optimization for memory-based operations. 

## Approach:

# Coarse-grained:
This implementation of the hash table just has one giant lock over the entire hash table. This allows us to ensure correctness of the table itself, but leads to some serious performance issues, which we hope to solve with the other models. Our goal with this table was to set a baseline for how a concurrent hash table would perform, so that we could compare the remainder of our results to it.

# Fine-grained:
When two threads are vying for access to the hash table, it may be possible that they are going to modify different buckets in the hash table. This is more likely when there are more number of buckets in the table. In such cases, it does not make sense to have a giant lock over the entire hash table. Instead, we have a lock for each bucket thus eliminating unnecessary waiting time for threads that are operating on different buckets.  

# Lock-free:
Lock-free data structures offer various benefits. Firstly they are non-blocking, i.e. it is guaranteed that a finite number of steps taken by a thread ensures progress of some operation unlike using locks wherein if a thread acquires a lock over some shared resource then no other thread can make any progress. Additionally, if a thread that has the lock fails for some reason then this could potentially prevent the other threads waiting on the lock from making any progress. However, implementing lock-free data structures can be quite tricky and ensuring correctness is a major challenge. One of the common problems is the ABA problem that arises because of using compare and exchange operations  to check if next pointer of a node has not changed. Another problem is with the deletion operation. The successor of the node being deleted must not change while the delete is happening. This may happen for instance, while inserting a node after the node to be deleted. What happens is that the predecessor of the node to be deleted ends up pointing to a stale successor. In order to avoid this, Harris proposed a two-step  approach wherein they mark the node to be deleted in the first step. At this stage the node is said to be logically deleted and no other nodes can be inserted after this node. In the second step, they physically remove the node from the list. While this method works well, Fomitchev pointed out their implementation can be inefficient for the following reason. Suppose a node has to be inserted after node X. At the same time X has been marked for deletion. This means that the node cannot be inserted after X now. So in the implementation of Harris the algorithm would restart the search for a suitable position to insert the node from the start of the list. Fomitchev suggests that each node have an additional attribute called ‘backlink’ which will point to the predecessor of a node if the node is marked for deletion. By doing so, we do not have to restart the search from the start of the list every time. We can traverse the backlink pointers till we reach an unmarked node and resume search from there. But the pitfall here, as highlighted by Fomitchev is that we can end up repeatedly traversing chains of backlinks from left to right while finding a position to insert. In order to avoid this, they introduce an additional flag bit which ensures that long chains of backlinks do not form. How this works is that when a node is to be deleted the predecessor is first flagged. Flagging means that the next pointer of the flagged node cannot be changed and the node cannot be marked for deletion. Once flagging is successful, the node is marked and deleted as before in two steps. Because the predecessor cannot be marked for deletion, long chains of backlinks cannot form. In our implementation, we embed the flag and mark bits in the next pointer of the node and use simple bit masking to extract these bits. We are able to do this because the dynamic memory allocated to nodes is at least 4-byte aligned. Here is an illustration of the 3 step delete.


<a href="418%20project%20proposal.pdf">View Proposal Here</a>

<a href="Final%20Project%20Checkpoint.pdf">View Checkpoint Here</a>

<a href="Final%20Report.pdf">View Final Report Here</a>

[[https://github.com/username/repository/blob/master/img/octocat.png|alt=octocat]]

