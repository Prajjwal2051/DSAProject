/**
 * QueueDS - Queue Data Structure Implementation
 * Follows FIFO (First In First Out) principle
 */
export class QueueDS {
    constructor() {
        this.items = [];
    }

    /**
     * Add element to the rear of the queue
     * @param {number} value - Value to enqueue
     */
    enqueue(value) {
        this.items.push(value);
    }

    /**
     * Remove element from the front of the queue
     * @returns {number} - Dequeued value
     */
    dequeue() {
        if (this.isEmpty()) {
            throw new Error('Queue Underflow');
        }
        return this.items.shift();
    }

    /**
     * Check if queue is empty
     * @returns {boolean}
     */
    isEmpty() {
        return this.items.length === 0;
    }

    /**
     * Get front element without removing it
     * @returns {number}
     */
    front() {
        if (this.isEmpty()) {
            return null;
        }
        return this.items[0];
    }

    /**
     * Get rear element
     * @returns {number}
     */
    rear() {
        if (this.isEmpty()) {
            return null;
        }
        return this.items[this.items.length - 1];
    }

    /**
     * Get queue data
     */
    getData() {
        return this.items;
    }

    /**
     * Get queue size
     */
    size() {
        return this.items.length;
    }

    /**
     * Clear all elements from the queue
     */
    clear() {
        this.items = [];
    }

    /**
     * Search for a value in the queue
     * @param {number} value - Value to search for
     * @returns {number} - Position from front, or -1 if not found
     */
    search(value) {
        return this.items.indexOf(value);
    }
}
