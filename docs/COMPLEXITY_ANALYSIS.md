# Time Complexity Analysis - Task Scheduler System

## Data Structures Overview

This document provides detailed time complexity analysis for all operations in the Task Scheduler System.

---

## 1. Linked List (Task History)

### Structure

- Node-based: Each node contains a Task and pointer to next node
- Maintains: Head and tail pointers for O(1) insertions at end

### Operations

| Operation            | Time Complexity | Space Complexity | Explanation                                                          |
| -------------------- | --------------- | ---------------- | -------------------------------------------------------------------- |
| **Insert at End**    | O(1)            | O(1)             | Direct access via tail pointer; update tail and previous node's next |
| **Display All**      | O(n)            | O(1)             | Must visit each of n nodes to print                                  |
| **Find Paused Task** | O(n)            | O(1)             | Linear search through all nodes                                      |
| **Free Memory**      | O(n)            | O(1)             | Must delete each node individually                                   |

### Why Linked List?

- **Dynamic size**: Tasks can be added to history without pre-allocation
- **Memory efficiency**: Only allocates space as needed
- **Sequential access**: History is typically viewed in order (FIFO display)
- **No reallocation**: Unlike arrays, no copying when expanding

---

## 2. Queue (FIFO Scheduling)

### Structure

- Linked list implementation: Front and rear pointers
- Node-based: Each node has Task data and next pointer

### Operations

| Operation        | Time Complexity | Space Complexity | Explanation                                               |
| ---------------- | --------------- | ---------------- | --------------------------------------------------------- |
| **Enqueue**      | O(1)            | O(1)             | Add to rear; update rear pointer and previous node's next |
| **Dequeue**      | O(1)            | O(1)             | Remove from front; update front pointer                   |
| **isEmpty**      | O(1)            | O(1)             | Simple null check on front pointer                        |
| **Display**      | O(n)            | O(1)             | Traverse from front to rear                               |
| **Remove by ID** | O(n)            | O(1)             | Linear search to find task with matching ID               |
| **Free Memory**  | O(n)            | O(1)             | Delete each node sequentially                             |

### Why Queue for FIFO?

- **Natural FIFO semantics**: First task added is first to execute
- **Constant time core operations**: Enqueue/Dequeue are O(1)
- **Simple implementation**: Straightforward pointer manipulation
- **Fairness**: Tasks are executed in arrival order

**Critical Property**: Both enqueue and dequeue are O(1) because we maintain both front and rear pointers, avoiding traversal.

---

## 3. Priority Queue (Priority Scheduling)

### Structure

- Binary Max-Heap: Array-based complete binary tree
- Max-Heap Property: Parent priority >= children priorities
- Array representation: Parent at i, children at 2i+1 and 2i+2

### Operations

| Operation        | Time Complexity | Space Complexity | Explanation                                            |
| ---------------- | --------------- | ---------------- | ------------------------------------------------------ |
| **Insert**       | O(log n)        | O(1) amortized   | Add at end, heapify-up to restore heap property        |
| **Extract Max**  | O(log n)        | O(1)             | Remove root, move last to root, heapify-down           |
| **isEmpty**      | O(1)            | O(1)             | Check if size == 0                                     |
| **Display**      | O(n)            | O(log n)         | Visit all n nodes; recursive call stack depth = height |
| **Remove by ID** | O(n)            | O(1)             | O(n) to find + O(log n) to heapify = O(n) total        |
| **Resize**       | O(n)            | O(n)             | Copy all elements to new array (rare, amortized O(1))  |
| **Heapify Up**   | O(log n)        | O(1)             | At most log n levels to bubble up                      |
| **Heapify Down** | O(log n)        | O(log n)         | At most log n levels; recursive (or iterative)         |

### Detailed Complexity Explanations

#### Insert - O(log n)

```
1. Add task at position 'size' (end of array) - O(1)
2. Compare with parent at (i-1)/2
3. If child > parent, swap and move up
4. Repeat until heap property satisfied
5. Maximum swaps = height of tree = log2(n)
```

#### Extract Max - O(log n)

```
1. Save root element (max priority) - O(1)
2. Move last element to root - O(1)
3. Compare root with children
4. Swap with larger child if necessary
5. Repeat down the tree
6. Maximum swaps = height = log2(n)
```

#### Remove by ID - O(n)

```
1. Linear search to find task - O(n) worst case
2. Replace with last element - O(1)
3. Heapify down OR heapify up - O(log n)
4. Total: O(n) + O(log n) = O(n)
```

### Why Binary Heap for Priority Queue?

- **Efficient priority operations**: Insert and extract are O(log n), much better than O(n) for unsorted array
- **Complete tree**: No wasted space; array is densely packed
- **Better than BST**: Simpler implementation; no balancing required
- **Cache friendly**: Array-based structure has good locality of reference

**Comparison with alternatives**:

- Unsorted array: Insert O(1), Extract O(n) - not good
- Sorted array: Insert O(n), Extract O(1) - not good
- Binary Heap: Insert O(log n), Extract O(log n) - best choice

---

## 4. Task Scheduler Operations

### High-Level Operations

| Operation        | Time Complexity  | Explanation                                                         |
| ---------------- | ---------------- | ------------------------------------------------------------------- |
| **Add Task**     | O(1) or O(log n) | O(1) for FIFO (queue enqueue), O(log n) for Priority (heap insert)  |
| **Execute Task** | O(1) or O(log n) | O(1) for FIFO (queue dequeue), O(log n) for Priority (heap extract) |
| **Pause Task**   | O(1)             | Delete running task pointer, add to history (O(1))                  |
| **Resume Task**  | O(n) + O(log n)  | O(n) to find in history, O(1) or O(log n) to add to queue           |
| **Remove Task**  | O(n)             | Search in queue/heap and remove                                     |
| **Display All**  | O(n)             | Display all queues and history                                      |
| **Switch Mode**  | O(1)             | Simple mode variable change (only allowed when queues empty)        |

---

## Space Complexity Analysis

### Overall Space Usage

| Component          | Space Complexity | Details                                    |
| ------------------ | ---------------- | ------------------------------------------ |
| **Queue**          | O(n)             | n nodes, each with Task data + pointer     |
| **Priority Queue** | O(n)             | Array of n task pointers + Tasks           |
| **Task History**   | O(m)             | m nodes for completed/paused/removed tasks |
| **Total**          | O(n + m)         | n = ready tasks, m = history tasks         |

### Per-Node Space

```c
Task: about 120 bytes (int + char[100] + int + int + enum)
QueueNode: about 128 bytes (Task + pointer)
HistoryNode: about 128 bytes (Task + pointer)
Heap entry: about 8 bytes (pointer) + 120 bytes (Task) = 128 bytes
```

---

## Best, Worst, and Average Cases

### Priority Queue Insert

| Case        | Complexity | Scenario                                            |
| ----------- | ---------- | --------------------------------------------------- |
| **Best**    | O(1)       | Inserted task has lowest priority (stays at bottom) |
| **Average** | O(log n)   | Task bubbles up partway                             |
| **Worst**   | O(log n)   | Task has highest priority (bubbles to root)         |

### Priority Queue Extract Max

| Case        | Complexity | Scenario                                 |
| ----------- | ---------- | ---------------------------------------- |
| **Best**    | O(log n)   | Last element still requires heapify down |
| **Average** | O(log n)   | Typical case                             |
| **Worst**   | O(log n)   | New root must sink to bottom             |

### Queue Remove by ID

| Case        | Complexity    | Scenario                 |
| ----------- | ------------- | ------------------------ |
| **Best**    | O(1)          | Task is at front         |
| **Average** | O(n/2) = O(n) | Task in middle           |
| **Worst**   | O(n)          | Task at end or not found |

---

## Algorithmic Choices - Justification

### 1. Why Not Use Array-Based Queue?

- **Dynamic sizing needed**: Don't know task count in advance
- **Inefficient dequeue**: Would require shifting all elements O(n)
- **Linked list advantage**: O(1) enqueue and dequeue

### 2. Why Binary Heap Over Balanced BST?

- **Simpler implementation**: No rotation logic needed
- **Better constants**: Heap operations have lower constant factors
- **Array efficiency**: Better cache locality than pointer-based tree
- **No balancing overhead**: Complete tree property automatic

### 3. Why Linked List for History?

- **Append-only**: Only add to end, never delete or modify
- **No random access needed**: Always display sequentially
- **Memory efficient**: No pre-allocation or resizing

---

## Summary Table - All Operations

| Operation            | Data Structure | Time     | Reason                        |
| -------------------- | -------------- | -------- | ----------------------------- |
| Enqueue ready task   | Queue          | O(1)     | Add to rear with tail pointer |
| Dequeue ready task   | Queue          | O(1)     | Remove from front             |
| Insert priority task | Max-Heap       | O(log n) | Heapify up from bottom        |
| Extract max priority | Max-Heap       | O(log n) | Heapify down from root        |
| Add to history       | Linked List    | O(1)     | Insert at tail                |
| Find paused task     | Linked List    | O(n)     | Linear search                 |
| Display queue        | Any            | O(n)     | Must visit all elements       |
| Remove by ID         | Queue/Heap     | O(n)     | Search then remove            |

---

## Optimization Opportunities (Not Implemented)

1. **Hash map for ID lookup**: Would make "remove by ID" O(1) average case
2. **Fibonacci heap**: Would improve insert to O(1) amortized
3. **Skip list for history**: Would allow O(log n) search for paused tasks

**Note**: These were not implemented to keep the code focused on fundamental data structures for educational purposes.

---

## Conclusion

The data structures were chosen to provide:

- Efficient core operations: O(1) or O(log n) for common tasks
- Educational clarity: Clear demonstration of heap, queue, and list
- Memory efficiency: Dynamic allocation without waste
- Correctness: Proper implementation of fundamental algorithms

**Total Implementation Compliance**:

- No STL containers
- Manual pointer-based structures
- Proper time complexities
- Clean memory management
