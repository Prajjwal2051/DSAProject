/**
 * Node - Represents a node in the binary tree
 */
export class Node {
    constructor(value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }
}

/**
 * BinaryTreeDS - Binary Search Tree Implementation
 */
export class BinaryTreeDS {
    constructor() {
        this.root = null;
    }

    /**
     * Insert a value into the binary search tree
     * @param {number} value - Value to insert
     */
    insert(value) {
        const newNode = new Node(value);
        
        if (this.root === null) {
            this.root = newNode;
        } else {
            this._insertNode(this.root, newNode);
        }
    }

    /**
     * Helper method to insert node recursively
     * @private
     */
    _insertNode(node, newNode) {
        if (newNode.value < node.value) {
            // Insert in left subtree
            if (node.left === null) {
                node.left = newNode;
            } else {
                this._insertNode(node.left, newNode);
            }
        } else {
            // Insert in right subtree
            if (node.right === null) {
                node.right = newNode;
            } else {
                this._insertNode(node.right, newNode);
            }
        }
    }

    /**
     * Perform inorder traversal (Left -> Root -> Right)
     * @returns {Array} - Array of values in inorder
     */
    inorder() {
        const result = [];
        this._inorderTraversal(this.root, result);
        return result;
    }

    _inorderTraversal(node, result) {
        if (node !== null) {
            this._inorderTraversal(node.left, result);
            result.push(node.value);
            this._inorderTraversal(node.right, result);
        }
    }

    /**
     * Perform preorder traversal (Root -> Left -> Right)
     * @returns {Array} - Array of values in preorder
     */
    preorder() {
        const result = [];
        this._preorderTraversal(this.root, result);
        return result;
    }

    _preorderTraversal(node, result) {
        if (node !== null) {
            result.push(node.value);
            this._preorderTraversal(node.left, result);
            this._preorderTraversal(node.right, result);
        }
    }

    /**
     * Perform postorder traversal (Left -> Right -> Root)
     * @returns {Array} - Array of values in postorder
     */
    postorder() {
        const result = [];
        this._postorderTraversal(this.root, result);
        return result;
    }

    _postorderTraversal(node, result) {
        if (node !== null) {
            this._postorderTraversal(node.left, result);
            this._postorderTraversal(node.right, result);
            result.push(node.value);
        }
    }

    /**
     * Get traversal result based on type
     * @param {string} type - 'inorder', 'preorder', or 'postorder'
     */
    traversal(type) {
        switch(type) {
            case 'inorder':
                return this.inorder();
            case 'preorder':
                return this.preorder();
            case 'postorder':
                return this.postorder();
            default:
                return [];
        }
    }

    /**
     * Get root node
     */
    getRoot() {
        return this.root;
    }

    /**
     * Check if tree is empty
     */
    isEmpty() {
        return this.root === null;
    }

    /**
     * Search for a value in the tree
     * @param {number} value - Value to search for
     * @returns {boolean} - True if found, false otherwise
     */
    search(value) {
        return this._searchNode(this.root, value);
    }

    _searchNode(node, value) {
        if (node === null) {
            return false;
        }
        if (value === node.value) {
            return true;
        }
        if (value < node.value) {
            return this._searchNode(node.left, value);
        }
        return this._searchNode(node.right, value);
    }

    /**
     * Get the height of the tree
     * @returns {number} - Height of tree
     */
    height() {
        return this._getHeight(this.root);
    }

    _getHeight(node) {
        if (node === null) {
            return 0;
        }
        const leftHeight = this._getHeight(node.left);
        const rightHeight = this._getHeight(node.right);
        return Math.max(leftHeight, rightHeight) + 1;
    }

    /**
     * Get minimum value in the tree
     * @returns {number} - Minimum value
     */
    findMin() {
        if (this.isEmpty()) {
            return null;
        }
        let current = this.root;
        while (current.left !== null) {
            current = current.left;
        }
        return current.value;
    }

    /**
     * Get maximum value in the tree
     * @returns {number} - Maximum value
     */
    findMax() {
        if (this.isEmpty()) {
            return null;
        }
        let current = this.root;
        while (current.right !== null) {
            current = current.right;
        }
        return current.value;
    }

    /**
     * Clear the tree
     */
    clear() {
        this.root = null;
    }

    /**
     * Count total nodes in the tree
     * @returns {number} - Total node count
     */
    count() {
        return this._countNodes(this.root);
    }

    _countNodes(node) {
        if (node === null) {
            return 0;
        }
        return 1 + this._countNodes(node.left) + this._countNodes(node.right);
    }
}
