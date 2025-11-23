/**
 * Main Application Controller
 * Manages UI interactions and visualization rendering
 */

import { ArrayDS } from './structures/array.js';
import { StackDS } from './structures/stack.js';
import { QueueDS } from './structures/queue.js';
import { BinaryTreeDS } from './structures/tree.js';

class DSAVisualizer {
    constructor() {
        // Initialize data structures
        this.array = new ArrayDS();
        this.stack = new StackDS();
        this.queue = new QueueDS();
        this.tree = new BinaryTreeDS();

        // Get DOM elements
        this.vizArea = document.getElementById('viz-area');
        this.structureSelect = document.getElementById('structure-select');
        
        // Set up event listeners
        this.setupEventListeners();
        
        // Initial render
        this.renderArray();
    }

    /**
     * Set up event listeners for structure selection
     */
    setupEventListeners() {
        this.structureSelect.addEventListener('change', () => {
            this.switchStructure();
        });
    }

    /**
     * Switch between different data structures
     */
    switchStructure() {
        const selected = this.structureSelect.value;
        
        // Hide all control panels
        document.querySelectorAll('.controls').forEach(panel => {
            panel.classList.add('hidden');
        });
        
        // Show selected control panel and render
        switch(selected) {
            case 'array':
                document.getElementById('array-controls').classList.remove('hidden');
                this.renderArray();
                break;
            case 'stack':
                document.getElementById('stack-controls').classList.remove('hidden');
                this.renderStack();
                break;
            case 'queue':
                document.getElementById('queue-controls').classList.remove('hidden');
                this.renderQueue();
                break;
            case 'tree':
                document.getElementById('tree-controls').classList.remove('hidden');
                this.renderTree();
                break;
        }
    }

    /**
     * Clear visualization area
     */
    clearViz() {
        this.vizArea.innerHTML = '';
    }

    // ==================== ARRAY OPERATIONS ====================

    /**
     * Insert element into array
     */
    arrayInsert() {
        const value = document.getElementById('array-value').value;
        const index = document.getElementById('array-index').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        const idx = index === '' ? this.array.size() : parseInt(index);
        const insertedIdx = this.array.insert(parseInt(value), idx);
        
        this.renderArray(insertedIdx);
        
        // Clear inputs
        document.getElementById('array-value').value = '';
        document.getElementById('array-index').value = '';
    }

    /**
     * Delete element from array
     */
    arrayDelete() {
        const index = document.getElementById('array-delete-index').value;
        
        if (index === '') {
            alert('Please enter an index');
            return;
        }
        
        try {
            this.array.delete(parseInt(index));
            this.renderArray();
            document.getElementById('array-delete-index').value = '';
        } catch (error) {
            alert(error.message);
        }
    }

    /**
     * Update element in array
     */
    arrayUpdate() {
        const index = document.getElementById('array-update-index').value;
        const value = document.getElementById('array-update-value').value;
        
        if (index === '' || value === '') {
            alert('Please enter both index and value');
            return;
        }
        
        try {
            const idx = this.array.update(parseInt(index), parseInt(value));
            this.renderArray(idx);
            document.getElementById('array-update-index').value = '';
            document.getElementById('array-update-value').value = '';
        } catch (error) {
            alert(error.message);
        }
    }

    /**
     * Search for element in array
     */
    arraySearch() {
        const value = document.getElementById('array-search-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        const index = this.array.search(parseInt(value));
        const resultDiv = document.getElementById('array-result');
        
        if (index === -1) {
            resultDiv.innerHTML = `<strong>Not found!</strong>`;
            this.renderArray();
        } else {
            resultDiv.innerHTML = `<strong>Found at index: ${index}</strong>`;
            this.renderArray(index);
        }
        
        document.getElementById('array-search-value').value = '';
    }

    /**
     * Clear array
     */
    arrayClear() {
        this.array.clear();
        this.renderArray();
        document.getElementById('array-result').innerHTML = '';
    }

    /**
     * Render array visualization
     */
    renderArray(highlightIndex = -1) {
        this.clearViz();
        
        const container = document.createElement('div');
        container.className = 'array-container';
        
        const data = this.array.getData();
        
        if (data.length === 0) {
            container.innerHTML = '<p>Array is empty. Insert elements to visualize.</p>';
        } else {
            data.forEach((value, index) => {
                const wrapper = document.createElement('div');
                
                const block = document.createElement('div');
                block.className = 'ds-block';
                block.textContent = value;
                
                if (index === highlightIndex) {
                    block.classList.add('highlight');
                }
                
                const indexLabel = document.createElement('div');
                indexLabel.className = 'array-index';
                indexLabel.textContent = `[${index}]`;
                
                wrapper.appendChild(block);
                wrapper.appendChild(indexLabel);
                container.appendChild(wrapper);
            });
        }
        
        this.vizArea.appendChild(container);
    }

    // ==================== STACK OPERATIONS ====================

    /**
     * Push element onto stack
     */
    stackPush() {
        const value = document.getElementById('stack-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        this.stack.push(parseInt(value));
        this.renderStack();
        
        document.getElementById('stack-value').value = '';
    }

    /**
     * Pop element from stack
     */
    stackPop() {
        try {
            this.stack.pop();
            this.renderStack();
        } catch (error) {
            this.clearViz();
            const errorDiv = document.createElement('div');
            errorDiv.className = 'error-message';
            errorDiv.textContent = error.message;
            this.vizArea.appendChild(errorDiv);
        }
    }

    /**
     * Render stack visualization
     */
    renderStack() {
        this.clearViz();
        
        const container = document.createElement('div');
        container.className = 'stack-container';
        
        const data = this.stack.getData();
        
        if (data.length === 0) {
            container.innerHTML = '<p>Stack is empty. Push elements to visualize.</p>';
        } else {
            data.forEach((value, index) => {
                const wrapper = document.createElement('div');
                wrapper.style.display = 'flex';
                wrapper.style.alignItems = 'center';
                
                const block = document.createElement('div');
                block.className = 'ds-block';
                block.textContent = value;
                
                // Highlight top element
                if (index === data.length - 1) {
                    block.classList.add('top');
                    const label = document.createElement('span');
                    label.className = 'stack-label';
                    label.textContent = '← TOP';
                    wrapper.appendChild(block);
                    wrapper.appendChild(label);
                } else {
                    wrapper.appendChild(block);
                }
                
                container.appendChild(wrapper);
            });
        }
        
        this.vizArea.appendChild(container);
    }

    // ==================== QUEUE OPERATIONS ====================

    /**
     * Enqueue element into queue
     */
    queueEnqueue() {
        const value = document.getElementById('queue-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        this.queue.enqueue(parseInt(value));
        this.renderQueue();
        
        document.getElementById('queue-value').value = '';
    }

    /**
     * Dequeue element from queue
     */
    queueDequeue() {
        try {
            this.queue.dequeue();
            this.renderQueue();
            document.getElementById('queue-result').innerHTML = '';
        } catch (error) {
            this.clearViz();
            const errorDiv = document.createElement('div');
            errorDiv.className = 'error-message';
            errorDiv.textContent = error.message;
            this.vizArea.appendChild(errorDiv);
        }
    }

    /**
     * Peek at front element
     */
    queuePeek() {
        const front = this.queue.front();
        const resultDiv = document.getElementById('queue-result');
        
        if (front === null) {
            resultDiv.innerHTML = '<strong>Queue is empty</strong>';
        } else {
            resultDiv.innerHTML = `<strong>Front element: ${front}</strong>`;
        }
    }

    /**
     * Search for element in queue
     */
    queueSearch() {
        const value = document.getElementById('queue-search-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        const position = this.queue.search(parseInt(value));
        const resultDiv = document.getElementById('queue-result');
        
        if (position === -1) {
            resultDiv.innerHTML = '<strong>Not found!</strong>';
        } else {
            resultDiv.innerHTML = `<strong>Found at position ${position} from front</strong>`;
        }
        
        document.getElementById('queue-search-value').value = '';
    }

    /**
     * Clear queue
     */
    queueClear() {
        this.queue.clear();
        this.renderQueue();
        document.getElementById('queue-result').innerHTML = '';
    }

    /**
     * Render queue visualization
     */
    renderQueue() {
        this.clearViz();
        
        const container = document.createElement('div');
        container.className = 'queue-container';
        
        const data = this.queue.getData();
        
        if (data.length === 0) {
            container.innerHTML = '<p>Queue is empty. Enqueue elements to visualize.</p>';
        } else {
            data.forEach((value, index) => {
                const wrapper = document.createElement('div');
                
                const block = document.createElement('div');
                block.className = 'ds-block';
                block.textContent = value;
                
                // Highlight front and rear
                if (index === 0) {
                    block.classList.add('front');
                }
                if (index === data.length - 1) {
                    block.classList.add('rear');
                }
                
                const label = document.createElement('div');
                label.className = 'queue-label';
                if (index === 0) {
                    label.textContent = 'FRONT';
                } else if (index === data.length - 1) {
                    label.textContent = 'REAR';
                }
                
                wrapper.appendChild(block);
                wrapper.appendChild(label);
                container.appendChild(wrapper);
            });
        }
        
        this.vizArea.appendChild(container);
    }

    // ==================== TREE OPERATIONS ====================

    /**
     * Insert element into tree
     */
    treeInsert() {
        const value = document.getElementById('tree-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        this.tree.insert(parseInt(value));
        this.renderTree();
        
        document.getElementById('tree-value').value = '';
    }

    /**
     * Perform tree traversal
     */
    treeTraversal(type) {
        if (this.tree.isEmpty()) {
            alert('Tree is empty. Insert elements first.');
            return;
        }
        
        const result = this.tree.traversal(type);
        const resultDiv = document.getElementById('traversal-result');
        resultDiv.innerHTML = `<strong>${type.toUpperCase()}:</strong> ${result.join(' → ')}`;
        
        // Highlight nodes during traversal
        this.renderTree(result);
    }

    /**
     * Search for value in tree
     */
    treeSearch() {
        const value = document.getElementById('tree-search-value').value;
        
        if (value === '') {
            alert('Please enter a value');
            return;
        }
        
        const found = this.tree.search(parseInt(value));
        const resultDiv = document.getElementById('traversal-result');
        
        if (found) {
            resultDiv.innerHTML = `<strong>Value ${value} found in tree!</strong>`;
            this.renderTree([parseInt(value)]);
        } else {
            resultDiv.innerHTML = `<strong>Value ${value} not found</strong>`;
            this.renderTree();
        }
        
        document.getElementById('tree-search-value').value = '';
    }

    /**
     * Get tree height
     */
    treeHeight() {
        if (this.tree.isEmpty()) {
            alert('Tree is empty');
            return;
        }
        
        const height = this.tree.height();
        const resultDiv = document.getElementById('traversal-result');
        resultDiv.innerHTML = `<strong>Tree Height: ${height}</strong>`;
    }

    /**
     * Find minimum value
     */
    treeFindMin() {
        if (this.tree.isEmpty()) {
            alert('Tree is empty');
            return;
        }
        
        const min = this.tree.findMin();
        const resultDiv = document.getElementById('traversal-result');
        resultDiv.innerHTML = `<strong>Minimum Value: ${min}</strong>`;
        this.renderTree([min]);
    }

    /**
     * Find maximum value
     */
    treeFindMax() {
        if (this.tree.isEmpty()) {
            alert('Tree is empty');
            return;
        }
        
        const max = this.tree.findMax();
        const resultDiv = document.getElementById('traversal-result');
        resultDiv.innerHTML = `<strong>Maximum Value: ${max}</strong>`;
        this.renderTree([max]);
    }

    /**
     * Count total nodes
     */
    treeCount() {
        const count = this.tree.count();
        const resultDiv = document.getElementById('traversal-result');
        resultDiv.innerHTML = `<strong>Total Nodes: ${count}</strong>`;
    }

    /**
     * Clear tree
     */
    treeClear() {
        this.tree.clear();
        this.renderTree();
        document.getElementById('traversal-result').innerHTML = '';
    }

    /**
     * Render tree visualization
     */
    renderTree(highlightSequence = []) {
        this.clearViz();
        
        const container = document.createElement('div');
        container.className = 'tree-container';
        
        if (this.tree.isEmpty()) {
            container.innerHTML = '<p>Tree is empty. Insert elements to visualize.</p>';
        } else {
            const root = this.tree.getRoot();
            this._renderNode(root, container, highlightSequence);
        }
        
        this.vizArea.appendChild(container);
    }

    /**
     * Recursively render tree nodes
     * @private
     */
    _renderNode(node, container, highlightSequence) {
        if (node === null) return;
        
        const nodeDiv = document.createElement('div');
        nodeDiv.className = 'tree-node';
        
        // Render node value
        const valueDiv = document.createElement('span');
        valueDiv.className = 'tree-node-value';
        valueDiv.textContent = node.value;
        
        // Highlight if in traversal sequence
        if (highlightSequence.includes(node.value)) {
            valueDiv.classList.add('highlight');
        }
        
        nodeDiv.appendChild(valueDiv);
        
        // Render children
        if (node.left !== null || node.right !== null) {
            const childrenDiv = document.createElement('div');
            childrenDiv.className = 'tree-children';
            
            if (node.left !== null) {
                const leftLabel = document.createElement('span');
                leftLabel.className = 'tree-label';
                leftLabel.textContent = '↙ Left: ';
                childrenDiv.appendChild(leftLabel);
                this._renderNode(node.left, childrenDiv, highlightSequence);
            }
            
            if (node.right !== null) {
                const rightLabel = document.createElement('span');
                rightLabel.className = 'tree-label';
                rightLabel.textContent = '↘ Right: ';
                childrenDiv.appendChild(rightLabel);
                this._renderNode(node.right, childrenDiv, highlightSequence);
            }
            
            nodeDiv.appendChild(childrenDiv);
        }
        
        container.appendChild(nodeDiv);
    }
}

// Initialize application when DOM is loaded
const app = new DSAVisualizer();

// Expose app instance to window for button onclick handlers
window.app = app;
