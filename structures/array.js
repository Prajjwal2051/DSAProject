/**
 * ArrayDS - Array Data Structure Implementation
 * Demonstrates basic array operations: insert and delete
 */
export class ArrayDS {
    constructor() {
        this.data = [];
    }

    /**
     * Insert a value at a specific index
     * @param {number} value - Value to insert
     * @param {number} index - Position to insert at
     */
    insert(value, index) {
        // If index is beyond current length, push to end
        if (index >= this.data.length) {
            this.data.push(value);
        } else if (index < 0) {
            // Insert at beginning if negative index
            this.data.unshift(value);
        } else {
            // Insert at specific position, shifting elements right
            this.data.splice(index, 0, value);
        }
        return index;
    }

    /**
     * Delete element at a specific index
     * @param {number} index - Position to delete from
     */
    delete(index) {
        if (index < 0 || index >= this.data.length) {
            throw new Error('Index out of bounds');
        }
        this.data.splice(index, 1);
        return index;
    }

    /**
     * Get current array data
     */
    getData() {
        return this.data;
    }

    /**
     * Get array length
     */
    size() {
        return this.data.length;
    }
}
