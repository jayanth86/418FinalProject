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



## The Challenge:
Depending on how many threads or processes are accessing this hash table, the nature of operations they are going to perform on it and the access patterns, we will have to take measures in our implementation that ensure data integrity without compromising on performance. Fine-grained locks and lockless data structures can cause subtle data races. There is also the potential to introduce deadlocks or livelocks if not careful. Even after these are overcome, there remains the possibility that the overhead incurred in overcoming these can offset the performance gains that we hope for by using lock-free data structures or fine-grained locks. Our code must also be efficient for varying workloads that may have different proportions of the above-mentioned operations. Additionally, our project considers the use of transactional memory for ease of synchronization without losing out much on performance. Since there are many variants of transactional memory implementations, we will look to examine what kind of access patterns have an adversarial effect on the variant we use in our project. 

After some work on the project, memory reclamation seems to be extremely challenging and difficult to implement with a lock free model. Resizing the hash table may also prove to be extremely difficult and will require a lot of work on our end.


## Resources
We will be writing our code from scratch but using reference implementations found <a href="https://github.com/huxia1124/ParallelContainers">here</a> and <a href="https://github.com/ssteinberg">here</a> as guidance. In order to compare the performance of our code on different workloads we will use the results from the paper ‘High Performance Dynamic Lock-Free Hash Tables and List-Based Sets’ by Michael M. Maged as our benchmark. We will also need access to transactional memory capable machines.


## Goals and Deliverables:
We believe that a comprehensive study of fine-grained locks, lock-free implementation and transactional memory based implementation will make for a complete project requiring 6 weeks of coding and testing. If we do get ahead schedule, we will consider incorporating the ‘expand’ functionality in our hash table which we are presently not planning to add due to complications in getting it correct within the given time-constraints.

In our final presentation, we hope to share visual representations of the comparative performance of the various implementations we have planned on different workloads and some insights we gained in the process. We will particularly look to assess the impact on performance when the ratio of read/write operations on the hash table is varied and also when the level of concurrency is stepped up.


## Platform:
We will be using C++ to code this project as we wish to have control over the code at a lower level and due to better familiarity with concurrent programming in C++. We plan to use the GHC machines to implement this project as recommended in the lecture. 


## Updated Schedule:

|      Week     |     Goal      |
| ------------- | ------------- |
| 19 Nov - 21 Nov  | Transactional memory - Jayanth, Siddharth  |
| 22 Nov - 25 Nov  | Transactional memory - Jayanth Testing Suite - Siddharth  |
| 26 Nov - 29 Nov  | If TM complete, incorporate memory reclamation (125%) and expand table functionality (150%), Testing - Jayanth, Siddharth |
| 30 Nov - 3 Dec  | Performance testing - Jayanth, Siddharth  |
| 3 Dec - 6 Dec  | Performance testing, Report - Jayanth, Siddharth |
| 7 Dec - 10 Dec  | Report - Jayanth, Siddharth  |
| 11 Dec - 14 Dec  | Buffer in case something goes wrong  |

<a href="418%20project%20proposal.pdf">View Proposal Here</a>

<a href="Final%20Project%20Checkpoint.pdf">View Checkpoint Here</a>

<a href="Final%20Report.pdf">View Final Report Here</a>

[[https://github.com/username/repository/blob/master/img/octocat.png|alt=octocat]]

