# Task Scheduler System - User Guide

## Overview

A terminal-based task scheduling system implementing fundamental data structures from scratch in C. Perfect for DSA lab submissions demonstrating Queue, Priority Queue (Binary Heap), and Linked List implementations.

## Features

- Manual Data Structure Implementations (No STL containers)
- Dual Scheduling Modes: FIFO and Priority-based
- Complete Task Lifecycle: Add, Execute, Pause, Resume, Remove
- Visual Display: See internal state of all data structures
- Memory Safe: Proper cleanup with no memory leaks

## Data Structures Implemented

### 1. Linked List (Task History)

- Stores completed, paused, and removed tasks
- Operations: Insert at end O(1), Display O(n)

### 2. Queue (FIFO Mode)

- Implemented using linked list
- Operations: Enqueue O(1), Dequeue O(1)

### 3. Priority Queue (Priority Mode)

- Implemented using Binary Max-Heap
- Operations: Insert O(log n), Extract-Max O(log n)
- Visual tree structure display

## Compilation & Execution

### Compile

```bash
gcc -o task_scheduler task_scheduler.c -std=c99 -Wall
```

### Run

```bash
./task_scheduler
```

## Usage Guide

### Main Menu Options

1. **Add New Task**

   - Enter task name, priority, and execution time
   - Task is added to ready queue based on current mode

2. **Execute Next Task**

   - FIFO mode: Executes first task in queue
   - Priority mode: Executes highest priority task
   - Simulates execution and moves to history

3. **Pause Running Task**

   - Pauses the currently running task
   - Moves task to history with PAUSED status

4. **Resume Paused Task**

   - Enter task ID to resume
   - Moves task back to ready queue

5. **Remove Task by ID**

   - Remove task from queue or running state
   - Moves to history with REMOVED status

6. **Display All Queues & History**

   - Shows current system state
   - Displays heap structure in priority mode

7. **Switch Scheduling Mode**

   - Toggle between FIFO and PRIORITY modes
   - Only allowed when queues are empty

8. **Exit**
   - Properly frees all allocated memory

## Example Workflow

### FIFO Mode Example

```
1. Add Task: "Compile Code" (Priority: 5, Time: 10s)
2. Add Task: "Run Tests" (Priority: 3, Time: 15s)
3. Add Task: "Deploy" (Priority: 8, Time: 20s)
4. Execute Next -> Executes "Compile Code" (first added)
5. Execute Next -> Executes "Run Tests"
6. Execute Next -> Executes "Deploy"
```

### Priority Mode Example

```
1. Add Task: "Compile Code" (Priority: 5, Time: 10s)
2. Add Task: "Run Tests" (Priority: 3, Time: 15s)
3. Add Task: "Deploy" (Priority: 8, Time: 20s)
4. Execute Next -> Executes "Deploy" (highest priority: 8)
5. Execute Next -> Executes "Compile Code" (priority: 5)
6. Execute Next -> Executes "Run Tests" (priority: 3)
```

## Task Status Flow

```
READY -> RUNNING -> COMPLETED (moved to history)
  |         |
REMOVED   PAUSED -> (can be resumed to READY)
```

## Input Validation

- Invalid menu choices are handled gracefully
- Non-numeric input is caught and rejected
- Operations on empty queues show appropriate warnings
- Cannot switch modes while tasks are in queue

## Memory Management

- All dynamic allocations use malloc
- Proper cleanup with free in cleanup functions
- Running task cleanup on exit
- No memory leaks (Valgrind safe)

## Code Structure

The code is organized into clear sections:

1. Enums and Constants - Task status and scheduling mode definitions
2. Task Structure - Task data with all required fields
3. Linked List Implementation - Manual implementation for history
4. Queue Implementation - FIFO implementation using linked nodes
5. Priority Queue Implementation - Binary max-heap implementation
6. Task Scheduler Functions - Main coordinator and menu system
7. Main Function - Entry point with welcome screen

## Technical Details

### Task Structure

```c
typedef struct {
    int id;              // Unique identifier
    char name[100];      // Task name
    int priority;        // Higher = more important
    int executionTime;   // Simulated duration
    TaskStatus status;   // Current state
} Task;
```

### Status Enum

```c
typedef enum {
    READY,      // In queue, waiting
    RUNNING,    // Currently executing
    PAUSED,     // Temporarily stopped
    COMPLETED,  // Finished execution
    REMOVED     // Deleted by user
} TaskStatus;
```

## Notes for Submission

- No STL Containers - All data structures built manually with pointers and structs
- Inline Comments - All operations explained with complexity annotations
- Terminal Output - Clear formatting with separators
- Modular Code - Separated into logical functions
- Memory Safe - Proper cleanup functions
- Educational - Demonstrates core DSA concepts clearly

## Testing Checklist

- Add tasks in both modes
- Execute tasks in FIFO order
- Execute tasks in priority order
- Pause and resume tasks
- Remove tasks by ID
- Display all data structures
- Handle invalid input
- Memory cleanup on exit
- Switch between modes

## Troubleshooting

**Issue**: Compilation error  
**Solution**: Ensure gcc supports C99 (use -std=c99 flag)

**Issue**: Cannot switch mode  
**Solution**: Execute or remove all tasks first

**Issue**: Task not found for resume  
**Solution**: Only paused tasks can be resumed; check task history

---

**Developed for**: Data Structures & Algorithms Laboratory  
**Language**: C (with manual memory management)  
**No External Libraries**: Pure implementation from scratch
