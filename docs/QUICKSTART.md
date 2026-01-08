# Task Scheduler System - Quick Start Guide

## Compile and Run

```bash
# Navigate to project directory
cd /home/prajjwal/Desktop/Coding/DSAProject

# Compile
gcc -o task_scheduler task_scheduler.c -std=c99 -Wall

# Run
./task_scheduler
```

## Quick Demo Workflow

### FIFO Mode Demo

1. Press Enter at welcome screen
2. Choose 1 - Add New Task
   - Name: "Task A", Priority: 5, Time: 10
3. Choose 1 again - Add another task
   - Name: "Task B", Priority: 8, Time: 15
4. Choose 2 - Execute Next Task
   - Should execute "Task A" (added first)
5. Choose 2 again
   - Should execute "Task B"
6. Choose 6 - Display All to see history

### Priority Mode Demo

1. Choose 7 - Switch to Priority Mode
2. Add tasks with different priorities
3. Execute tasks - highest priority runs first

### Pause/Resume Demo

1. Add a task and choose 2 to execute
2. Choose 3 to pause it
3. Choose 4 and enter task ID to resume

## Features Summary

- Queue (FIFO) using linked list
- Priority Queue using binary max-heap
- Linked List for task history
- Add/Execute/Pause/Resume/Remove tasks
- Visual heap structure display
- Memory leak-free implementation
- Complete error handling

## Project Files

- task_scheduler.c - Main source code
- README.md - Comprehensive documentation
- COMPLEXITY_ANALYSIS.md - Time/space complexity analysis
- task_scheduler - Compiled executable

## Key Requirements Met

- No STL containers - All manual implementations
- Terminal only - Pure console application
- Inline comments - All operations documented
- State display - Output after every operation
- Clean code - Modular and readable

Perfect for DSA lab submission!
