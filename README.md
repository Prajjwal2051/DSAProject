# DSA Visualizer

An interactive web application for visualizing fundamental data structures and their operations.

## Features

- **Array**: Insert and delete operations with index-based visualization
- **Stack**: Push and pop with LIFO (Last In First Out) demonstration
- **Queue**: Enqueue and dequeue with FIFO (First In First Out) demonstration
- **Binary Search Tree**: Insert nodes and perform tree traversals (Inorder, Preorder, Postorder)

## How to Run

Simply open `index.html` in any modern web browser:

```bash
open index.html
```

For environments with strict CORS policies, use a local server:

```bash
python -m http.server 8000
```

Then navigate to `http://localhost:8000`

## Technology

- Pure HTML, CSS, and JavaScript (ES6 Modules)
- No external libraries or frameworks
- Clean, educational code focused on clarity

## Project Structure

```
/
├── index.html          # Main UI
├── style.css           # Styling
├── app.js              # Application controller
└── structures/         # Data structure implementations
    ├── array.js
    ├── stack.js
    ├── queue.js
    ├── linkedlist.js
    └── tree.js
```

## Usage

1. Select a data structure from the dropdown
2. Enter values and perform operations using the control panel
3. Watch the visualization update in real-time

## Educational Purpose

This visualizer is designed to help students understand how data structures work internally by providing immediate visual feedback for each operation.
