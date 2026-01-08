#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize queue
void initQueue(TaskQueue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
}

// Add task to rear of queue - Time Complexity: O(1)
void enqueue(TaskQueue* queue, Task task) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->task = task;
    newNode->next = NULL;
    
    if (queue->rear == NULL) {
        // Queue is empty
        queue->front = queue->rear = newNode;
    } else {
        // Add to rear
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->count++;
}

// Remove task from front of queue - Time Complexity: O(1)
Task dequeue(TaskQueue* queue) {
    if (queue->front == NULL) {
        printf("  Error: Queue is empty!\n");
        Task emptyTask = {0};
        return emptyTask;
    }
    
    QueueNode* temp = queue->front;
    Task task = queue->front->task;
    queue->front = queue->front->next;
    
    if (queue->front == NULL) {
        queue->rear = NULL;  // Queue is now empty
    }
    
    free(temp);
    queue->count--;
    return task;
}

// Check if queue is empty - Time Complexity: O(1)
int isQueueEmpty(const TaskQueue* queue) {
    return queue->front == NULL;
}

// Display queue contents - Time Complexity: O(n)
void displayQueue(const TaskQueue* queue) {
    if (queue->front == NULL) {
        printf("  [Empty]\n");
        return;
    }
    
    printf("  %-5s %-25s %-12s %-15s\n", "ID", "Name", "Priority", "Exec Time");
    printf("  ---------------------------------------------------------\n");
    
    QueueNode* current = queue->front;
    while (current != NULL) {
        printf("  %-5d %-25s %-12d %-15ds\n",
               current->task.id,
               current->task.name,
               current->task.priority,
               current->task.executionTime);
        current = current->next;
    }
}

// Remove task by ID from queue - Time Complexity: O(n)
int removeFromQueue(TaskQueue* queue, int id) {
    if (queue->front == NULL) return 0;
    
    // Special case: removing front element
    if (queue->front->task.id == id) {
        QueueNode* temp = queue->front;
        queue->front = queue->front->next;
        if (queue->front == NULL) queue->rear = NULL;
        free(temp);
        queue->count--;
        return 1;
    }
    
    // Search for task
    QueueNode* current = queue->front;
    while (current->next != NULL) {
        if (current->next->task.id == id) {
            QueueNode* temp = current->next;
            current->next = temp->next;
            if (temp == queue->rear) queue->rear = current;
            free(temp);
            queue->count--;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// Free all memory used by queue - Time Complexity: O(n)
void freeQueue(TaskQueue* queue) {
    while (queue->front != NULL) {
        QueueNode* temp = queue->front;
        queue->front = queue->front->next;
        free(temp);
    }
    queue->rear = NULL;
    queue->count = 0;
}
