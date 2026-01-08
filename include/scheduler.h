#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "task.h"
#include "queue.h"
#include "priority_queue.h"
#include "linked_list.h"

// Global state for task scheduler
typedef struct {
    TaskQueue readyQueue;
    PriorityQueue priorityQueue;
    TaskHistory history;
    SchedulingMode mode;
    int nextTaskId;
    Task* runningTask;
} TaskScheduler;

// Function declarations
void initScheduler(TaskScheduler* scheduler);
void addTask(TaskScheduler* scheduler);
void executeNextTask(TaskScheduler* scheduler);
void pauseTask(TaskScheduler* scheduler);
void resumeTask(TaskScheduler* scheduler);
void removeTask(TaskScheduler* scheduler);
void displayAll(const TaskScheduler* scheduler);
void switchMode(TaskScheduler* scheduler);
void runScheduler(TaskScheduler* scheduler);
void cleanupScheduler(TaskScheduler* scheduler);

#endif // SCHEDULER_H
