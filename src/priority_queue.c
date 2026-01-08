#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

// Helper functions for heap navigation
static int parent(int i) { return (i - 1) / 2; }
static int leftChild(int i) { return 2 * i + 1; }
static int rightChild(int i) { return 2 * i + 2; }

// Swap two tasks in heap - Time Complexity: O(1)
static void swapTasks(Task** a, Task** b) {
    Task* temp = *a;
    *a = *b;
    *b = temp;
}

// Initialize priority queue
void initPriorityQueue(PriorityQueue* pq, int capacity) {
    pq->heap = (Task**)malloc(capacity * sizeof(Task*));
    pq->capacity = capacity;
    pq->size = 0;
}

// Heapify up - restore heap property after insertion - Time Complexity: O(log n)
static void heapifyUp(PriorityQueue* pq, int index) {
    // Max heap: parent should have higher priority than children
    while (index > 0 && pq->heap[parent(index)]->priority < pq->heap[index]->priority) {
        swapTasks(&pq->heap[index], &pq->heap[parent(index)]);
        index = parent(index);
    }
}

// Heapify down - restore heap property after extraction - Time Complexity: O(log n)
static void heapifyDown(PriorityQueue* pq, int index) {
    int maxIndex = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    // Find largest priority among node and its children
    if (left < pq->size && pq->heap[left]->priority > pq->heap[maxIndex]->priority) {
        maxIndex = left;
    }
    if (right < pq->size && pq->heap[right]->priority > pq->heap[maxIndex]->priority) {
        maxIndex = right;
    }
    
    // If largest is not root, swap and continue heapifying
    if (maxIndex != index) {
        swapTasks(&pq->heap[index], &pq->heap[maxIndex]);
        heapifyDown(pq, maxIndex);
    }
}

// Resize heap when full - Time Complexity: O(n)
static void resizeHeap(PriorityQueue* pq) {
    pq->capacity *= 2;
    Task** newHeap = (Task**)malloc(pq->capacity * sizeof(Task*));
    for (int i = 0; i < pq->size; i++) {
        newHeap[i] = pq->heap[i];
    }
    free(pq->heap);
    pq->heap = newHeap;
}

// Insert task into priority queue - Time Complexity: O(log n)
void insertPQ(PriorityQueue* pq, Task task) {
    if (pq->size == pq->capacity) {
        resizeHeap(pq);
    }
    
    // Create new task on heap and insert
    Task* newTask = (Task*)malloc(sizeof(Task));
    *newTask = task;
    pq->heap[pq->size] = newTask;
    heapifyUp(pq, pq->size);
    pq->size++;
}

// Extract maximum priority task - Time Complexity: O(log n)
Task extractMax(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("  Error: Priority Queue is empty!\n");
        Task emptyTask = {0};
        return emptyTask;
    }
    
    Task maxTask = *(pq->heap[0]);
    free(pq->heap[0]);  // Free the extracted task
    
    // Move last element to root and heapify down
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;
    
    if (pq->size > 0) {
        heapifyDown(pq, 0);
    }
    
    return maxTask;
}

// Check if priority queue is empty - Time Complexity: O(1)
int isPQEmpty(const PriorityQueue* pq) {
    return pq->size == 0;
}

// Display heap structure recursively
static void displayTreeHelper(const PriorityQueue* pq, int index, int level) {
    if (index >= pq->size) return;
    
    // Display right subtree first
    if (rightChild(index) < pq->size) {
        displayTreeHelper(pq, rightChild(index), level + 1);
    }
    
    // Display current node with indentation
    for (int i = 0; i < level; i++) printf("      ");
    printf("|-- [%d] %s (P:%d)\n", 
           pq->heap[index]->id, 
           pq->heap[index]->name,
           pq->heap[index]->priority);
    
    // Display left subtree
    if (leftChild(index) < pq->size) {
        displayTreeHelper(pq, leftChild(index), level + 1);
    }
}

// Display priority queue with tree structure - Time Complexity: O(n)
void displayPQ(const PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("  [Empty]\n");
        return;
    }
    
    printf("\n  Binary Heap Structure (Max-Heap by Priority):\n");
    printf("  --------------------------------------------------\n");
    displayTreeHelper(pq, 0, 0);
    
    printf("\n  Heap Array View:\n");
    printf("  %-5s %-5s %-25s %-12s\n", "Idx", "ID", "Name", "Priority");
    printf("  -----------------------------------------------\n");
    
    for (int i = 0; i < pq->size; i++) {
        printf("  %-5d %-5d %-25s %-12d\n",
               i, pq->heap[i]->id, pq->heap[i]->name, pq->heap[i]->priority);
    }
}

// Remove task by ID from priority queue - Time Complexity: O(n)
int removeFromPQ(PriorityQueue* pq, int id) {
    // Find task in heap
    int index = -1;
    for (int i = 0; i < pq->size; i++) {
        if (pq->heap[i]->id == id) {
            index = i;
            break;
        }
    }
    
    if (index == -1) return 0;
    
    free(pq->heap[index]);  // Free the task
    
    // Replace with last element
    pq->heap[index] = pq->heap[pq->size - 1];
    pq->size--;
    
    if (pq->size > 0 && index < pq->size) {
        // Restore heap property
        heapifyDown(pq, index);
        heapifyUp(pq, index);
    }
    
    return 1;
}

// Free all memory used by priority queue - Time Complexity: O(n)
void freePQ(PriorityQueue* pq) {
    for (int i = 0; i < pq->size; i++) {
        free(pq->heap[i]);
    }
    free(pq->heap);
    pq->size = 0;
}
