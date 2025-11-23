/**
 * StackDS - Stack Data Structure Implementation
 * Follows LIFO (Last In First Out) principle
 */
export class StackDS {
    constructor() {
        this.items = [];
    }

    /**
     * Push element onto the stack
     * @param {number} value - Value to push
     */
    push(value) {
        this.items.push(value);
    }

    /**
     * Pop element from the stack
     * @returns {number} - Popped value
     */
    pop() {
        if (this.isEmpty()) {
            throw new Error('Stack Underflow');
        }
        return this.items.pop();
    }

    /**
     * Check if stack is empty
     * @returns {boolean}
     */
    isEmpty() {
        return this.items.length === 0;
    }

    /**
     * Get top element without removing it
     * @returns {number}
     */
    peek() {
        if (this.isEmpty()) {
            return null;
        }
        return this.items[this.items.length - 1];
    }

    /**
     * Get stack data
     */
    getData() {
        return this.items;
    }

    /**
     * Get stack size
     */
    size() {
        return this.items.length;
    }

    /**
     * Clear all elements from the stack
     */
    clear() {
        this.items = [];
    }

    /**
     * Search for a value in the stack
     * @param {number} value - Value to search for
     * @returns {number} - Position from top (0 = top), or -1 if not found
     */
    search(value) {
        for (let i = this.items.length - 1; i >= 0; i--) {
            if (this.items[i] === value) {
                return this.items.length - 1 - i;
            }
        }
        return -1;
    }
}
