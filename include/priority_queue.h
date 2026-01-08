#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "task.h"

// Priority queue structure using binary max-heap
typedef struct {
    Task** heap;       // Array of Task pointers
    int capacity;
    int size;
} PriorityQueue;

// Function declarations
void initPriorityQueue(PriorityQueue* pq, int capacity);
void insertPQ(PriorityQueue* pq, Task task);
Task extractMax(PriorityQueue* pq);
int isPQEmpty(const PriorityQueue* pq);
void displayPQ(const PriorityQueue* pq);
int removeFromPQ(PriorityQueue* pq, int id);
void freePQ(PriorityQueue* pq);

#endif // PRIORITY_QUEUE_H
