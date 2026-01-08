#ifndef TASK_H
#define TASK_H

// Task status definitions
typedef enum {
    READY,
    RUNNING,
    PAUSED,
    COMPLETED,
    REMOVED
} TaskStatus;

// Scheduling mode definitions
typedef enum {
    FIFO,
    PRIORITY
} SchedulingMode;

// Task structure containing all task information
typedef struct {
    int id;
    char name[100];
    int priority;        // Higher value means higher priority
    int executionTime;   // Simulated execution time in seconds
    TaskStatus status;
} Task;

// Function declarations
const char* statusToString(TaskStatus status);
Task createTask(int id, const char* name, int priority, int execTime);

#endif // TASK_H
