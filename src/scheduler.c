#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize scheduler
void initScheduler(TaskScheduler* scheduler) {
    initQueue(&scheduler->readyQueue);
    initPriorityQueue(&scheduler->priorityQueue, 10);
    initHistory(&scheduler->history);
    scheduler->mode = FIFO;
    scheduler->nextTaskId = 1;
    scheduler->runningTask = NULL;
}

// Display header
static void displayHeader(const TaskScheduler* scheduler) {
    printf("\n");
    printf("  ==================================================\n");
    printf("         TASK SCHEDULER SYSTEM - DSA LAB          \n");
    printf("  ==================================================\n");
    printf("  Current Mode: %s\n", 
           scheduler->mode == FIFO ? "FIFO (First In First Out)" : 
                                    "PRIORITY (Highest Priority First)");
    printf("  ==================================================\n\n");
}

// Add a new task
void addTask(TaskScheduler* scheduler) {
    char name[100];
    int priority, execTime;
    
    printf("\n  ADD NEW TASK\n");
    printf("  ------------------------------\n");
    
    printf("  Enter task name: ");
    getchar();  // Clear newline
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = 0;  // Remove newline
    
    printf("  Enter priority (higher = more important): ");
    scanf("%d", &priority);
    
    printf("  Enter execution time (seconds): ");
    scanf("%d", &execTime);
    
    Task newTask = createTask(scheduler->nextTaskId++, name, priority, execTime);
    
    // Add to appropriate queue based on mode
    if (scheduler->mode == FIFO) {
        enqueue(&scheduler->readyQueue, newTask);
    } else {
        insertPQ(&scheduler->priorityQueue, newTask);
    }
    
    printf("\n  Task added successfully with ID: %d\n", newTask.id);
    
    // Display updated queue
    printf("\n  Updated Ready Queue:\n");
    if (scheduler->mode == FIFO) {
        displayQueue(&scheduler->readyQueue);
    } else {
        displayPQ(&scheduler->priorityQueue);
    }
}

// Execute next task
void executeNextTask(TaskScheduler* scheduler) {
    if (scheduler->runningTask != NULL) {
        printf("\n  Warning: A task is already running: [%d] %s\n", 
               scheduler->runningTask->id, scheduler->runningTask->name);
        printf("  Pause or complete the current task before executing another.\n");
        return;
    }
    
    Task taskToExecute;
    
    if (scheduler->mode == FIFO) {
        if (isQueueEmpty(&scheduler->readyQueue)) {
            printf("\n  Warning: No tasks in ready queue!\n");
            return;
        }
        taskToExecute = dequeue(&scheduler->readyQueue);
    } else {
        if (isPQEmpty(&scheduler->priorityQueue)) {
            printf("\n  Warning: No tasks in priority queue!\n");
            return;
        }
        taskToExecute = extractMax(&scheduler->priorityQueue);
    }
    
    taskToExecute.status = RUNNING;
    scheduler->runningTask = (Task*)malloc(sizeof(Task));
    *(scheduler->runningTask) = taskToExecute;
    
    printf("\n  EXECUTING TASK\n");
    printf("  ------------------------------\n");
    printf("  ID: %d\n", scheduler->runningTask->id);
    printf("  Name: %s\n", scheduler->runningTask->name);
    printf("  Priority: %d\n", scheduler->runningTask->priority);
    printf("  Execution Time: %d seconds\n", scheduler->runningTask->executionTime);
    printf("  Status: %s\n", statusToString(scheduler->runningTask->status));
    
    // Simulate execution
    printf("\n  Simulating execution...\n");
    
    // Mark as completed
    scheduler->runningTask->status = COMPLETED;
    addToHistory(&scheduler->history, *(scheduler->runningTask));
    
    printf("\n  Task completed and moved to history!\n");
    
    free(scheduler->runningTask);
    scheduler->runningTask = NULL;
}

// Pause running task
void pauseTask(TaskScheduler* scheduler) {
    if (scheduler->runningTask == NULL) {
        printf("\n  Warning: No task is currently running!\n");
        return;
    }
    
    scheduler->runningTask->status = PAUSED;
    printf("\n  Task paused: [%d] %s\n", 
           scheduler->runningTask->id, scheduler->runningTask->name);
    
    addToHistory(&scheduler->history, *(scheduler->runningTask));
    
    free(scheduler->runningTask);
    scheduler->runningTask = NULL;
    
    printf("  Task moved to history as PAUSED.\n");
}

// Resume paused task
void resumeTask(TaskScheduler* scheduler) {
    int id;
    printf("\n  Enter task ID to resume: ");
    scanf("%d", &id);
    
    Task* pausedTask = findPausedTask(&scheduler->history, id);
    if (pausedTask == NULL) {
        printf("\n  Warning: No paused task found with ID: %d\n", id);
        return;
    }
    
    Task resumedTask = *pausedTask;
    resumedTask.status = READY;
    
    // Add back to appropriate queue
    if (scheduler->mode == FIFO) {
        enqueue(&scheduler->readyQueue, resumedTask);
    } else {
        insertPQ(&scheduler->priorityQueue, resumedTask);
    }
    
    printf("\n  Task resumed: [%d] %s\n", resumedTask.id, resumedTask.name);
    printf("  Task added back to ready queue.\n");
}

// Remove task by ID
void removeTask(TaskScheduler* scheduler) {
    int id;
    printf("\n  Enter task ID to remove: ");
    scanf("%d", &id);
    
    int found = 0;
    
    // Check if it's the running task
    if (scheduler->runningTask != NULL && scheduler->runningTask->id == id) {
        scheduler->runningTask->status = REMOVED;
        addToHistory(&scheduler->history, *(scheduler->runningTask));
        free(scheduler->runningTask);
        scheduler->runningTask = NULL;
        found = 1;
        printf("\n  Running task removed and moved to history.\n");
        return;
    }
    
    // Try to remove from queue
    if (scheduler->mode == FIFO) {
        found = removeFromQueue(&scheduler->readyQueue, id);
    } else {
        found = removeFromPQ(&scheduler->priorityQueue, id);
    }
    
    if (found) {
        Task removedTask = createTask(id, "Removed Task", 0, 0);
        removedTask.status = REMOVED;
        addToHistory(&scheduler->history, removedTask);
        printf("\n  Task removed from queue and moved to history.\n");
    } else {
        printf("\n  Warning: Task with ID %d not found.\n", id);
    }
}

// Display all queues and history
void displayAll(const TaskScheduler* scheduler) {
    printf("\n  CURRENT SYSTEM STATE\n");
    printf("  ==================================================\n");
    
    if (scheduler->runningTask != NULL) {
        printf("\n  RUNNING TASK:\n");
        printf("  ------------------------------\n");
        printf("  [%d] %s (Priority: %d)\n", 
               scheduler->runningTask->id,
               scheduler->runningTask->name,
               scheduler->runningTask->priority);
    } else {
        printf("\n  RUNNING TASK: None\n");
    }
    
    printf("\n  READY QUEUE (%s Mode):\n", 
           scheduler->mode == FIFO ? "FIFO" : "PRIORITY");
    printf("  ------------------------------\n");
    if (scheduler->mode == FIFO) {
        displayQueue(&scheduler->readyQueue);
    } else {
        displayPQ(&scheduler->priorityQueue);
    }
    
    printf("\n  TASK HISTORY (Completed/Paused/Removed):\n");
    printf("  ------------------------------\n");
    displayHistory(&scheduler->history);
}

// Switch scheduling mode
void switchMode(TaskScheduler* scheduler) {
    if (!isQueueEmpty(&scheduler->readyQueue) || !isPQEmpty(&scheduler->priorityQueue)) {
        printf("\n  Warning: Cannot switch mode while tasks are in queue!\n");
        printf("  Please execute or remove all tasks first.\n");
        return;
    }
    
    scheduler->mode = (scheduler->mode == FIFO) ? PRIORITY : FIFO;
    printf("\n  Switched to %s mode.\n", 
           scheduler->mode == FIFO ? "FIFO" : "PRIORITY");
}

// Main menu loop
void runScheduler(TaskScheduler* scheduler) {
    int choice;
    
    while (1) {
        displayHeader(scheduler);
        
        printf("  MAIN MENU\n");
        printf("  ------------------------------\n");
        printf("  1. Add New Task\n");
        printf("  2. Execute Next Task\n");
        printf("  3. Pause Running Task\n");
        printf("  4. Resume Paused Task\n");
        printf("  5. Remove Task by ID\n");
        printf("  6. Display All Queues & History\n");
        printf("  7. Switch Scheduling Mode\n");
        printf("  8. Exit\n");
        printf("  ------------------------------\n");
        printf("  Enter choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("\n  Warning: Invalid input! Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            printf("  Press Enter to continue...");
            getchar();
            continue;
        }
        
        switch (choice) {
            case 1:
                addTask(scheduler);
                break;
            case 2:
                executeNextTask(scheduler);
                break;
            case 3:
                pauseTask(scheduler);
                break;
            case 4:
                resumeTask(scheduler);
                break;
            case 5:
                removeTask(scheduler);
                break;
            case 6:
                displayAll(scheduler);
                break;
            case 7:
                switchMode(scheduler);
                break;
            case 8:
                printf("\n  Exiting program...\n");
                printf("  Cleaning up memory...\n");
                if (scheduler->runningTask != NULL) {
                    free(scheduler->runningTask);
                }
                freeQueue(&scheduler->readyQueue);
                freePQ(&scheduler->priorityQueue);
                freeHistory(&scheduler->history);
                printf("  All memory freed successfully!\n");
                printf("  Goodbye!\n\n");
                return;
            default:
                printf("\n  Warning: Invalid choice! Please enter 1-8.\n");
        }
        
        printf("\n  Press Enter to continue...");
        while (getchar() != '\n');  // Clear buffer
        getchar();
    }
}

// Cleanup scheduler resources
void cleanupScheduler(TaskScheduler* scheduler) {
    if (scheduler->runningTask != NULL) {
        free(scheduler->runningTask);
    }
    freeQueue(&scheduler->readyQueue);
    freePQ(&scheduler->priorityQueue);
    freeHistory(&scheduler->history);
}
