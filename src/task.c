#include "task.h"
#include <string.h>

// Convert status enum to string for display
const char* statusToString(TaskStatus status) {
    switch(status) {
        case READY: return "READY";
        case RUNNING: return "RUNNING";
        case PAUSED: return "PAUSED";
        case COMPLETED: return "COMPLETED";
        case REMOVED: return "REMOVED";
        default: return "UNKNOWN";
    }
}

// Create and initialize a new task
Task createTask(int id, const char* name, int priority, int execTime) {
    Task t;
    t.id = id;
    strncpy(t.name, name, 99);
    t.name[99] = '\0';
    t.priority = priority;
    t.executionTime = execTime;
    t.status = READY;
    return t;
}
