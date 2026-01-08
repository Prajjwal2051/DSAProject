#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

// Initialize task history
void initHistory(TaskHistory* history) {
    history->head = NULL;
    history->tail = NULL;
    history->count = 0;
}

// Add task to history - Time Complexity: O(1) with tail pointer
void addToHistory(TaskHistory* history, Task task) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    newNode->task = task;
    newNode->next = NULL;
    
    if (history->tail == NULL) {
        // List is empty
        history->head = history->tail = newNode;
    } else {
        // Append to end
        history->tail->next = newNode;
        history->tail = newNode;
    }
    history->count++;
}

// Display all tasks in history - Time Complexity: O(n)
void displayHistory(const TaskHistory* history) {
    if (history->head == NULL) {
        printf("  [Empty]\n");
        return;
    }
    
    printf("  %-5s %-25s %-12s %-12s\n", "ID", "Name", "Priority", "Status");
    printf("  ------------------------------------------------------\n");
    
    HistoryNode* current = history->head;
    while (current != NULL) {
        printf("  %-5d %-25s %-12d %-12s\n", 
               current->task.id,
               current->task.name,
               current->task.priority,
               statusToString(current->task.status));
        current = current->next;
    }
}

// Find paused task by ID - Time Complexity: O(n)
Task* findPausedTask(TaskHistory* history, int id) {
    HistoryNode* current = history->head;
    while (current != NULL) {
        if (current->task.id == id && current->task.status == PAUSED) {
            return &(current->task);
        }
        current = current->next;
    }
    return NULL;
}

// Free all memory used by history - Time Complexity: O(n)
void freeHistory(TaskHistory* history) {
    HistoryNode* current = history->head;
    while (current != NULL) {
        HistoryNode* temp = current;
        current = current->next;
        free(temp);
    }
    history->head = history->tail = NULL;
    history->count = 0;
}
