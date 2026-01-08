#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "task.h"

// Node structure for linked list
typedef struct HistoryNode {
    Task task;
    struct HistoryNode* next;
} HistoryNode;

// Linked list structure for task history
typedef struct {
    HistoryNode* head;
    HistoryNode* tail;
    int count;
} TaskHistory;

// Function declarations
void initHistory(TaskHistory* history);
void addToHistory(TaskHistory* history, Task task);
void displayHistory(const TaskHistory* history);
Task* findPausedTask(TaskHistory* history, int id);
void freeHistory(TaskHistory* history);

#endif // LINKED_LIST_H
