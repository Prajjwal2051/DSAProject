#ifndef QUEUE_H
#define QUEUE_H

#include "task.h"

// Node structure for queue
typedef struct QueueNode {
    Task task;
    struct QueueNode* next;
} QueueNode;

// Queue structure
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int count;
} TaskQueue;

// Function declarations
void initQueue(TaskQueue* queue);
void enqueue(TaskQueue* queue, Task task);
Task dequeue(TaskQueue* queue);
int isQueueEmpty(const TaskQueue* queue);
void displayQueue(const TaskQueue* queue);
int removeFromQueue(TaskQueue* queue, int id);
void freeQueue(TaskQueue* queue);

#endif // QUEUE_H
