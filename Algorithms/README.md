# Data Structures Implementations in C++

This repository contains educational C++ implementations of various data structures for teaching purposes.

## Files

### Linked Lists
1. **singly_linked_list.cpp** - Single/Singly Linked List
2. **doubly_linked_list.cpp** - Doubly Linked List
3. **circular_linked_list.cpp** - Circular Linked List

### Stack
4. **stack_array.cpp** - Stack (Array-based Implementation)
5. **stack_linked_list.cpp** - Stack (Linked List-based Implementation)

### Queue
6. **queue_array.cpp** - Queue (Array-based Implementation)
7. **queue_linked_list.cpp** - Queue (Linked List-based Implementation)

### Double-ended Queue (Deque)
8. **deque_array.cpp** - Deque (Array-based Implementation)
9. **deque_linked_list.cpp** - Deque (Linked List-based Implementation)

## Features

Each implementation includes:

- **Node Structure**: Clear definition of the node structure
- **Basic Operations**:
  - Insert at beginning
  - Insert at end
  - Insert at position
  - Delete by value
  - Delete at position
  - Search
  - Display
  - Get size
- **Additional Operations**:
  - Reverse (for singly and doubly linked lists)
  - Forward/Backward display (for doubly linked list)
  - Circular verification (for circular linked list)

## How to Compile and Run

### Using g++:

```bash
# Compile singly linked list
g++ -o singly singly_linked_list.cpp
./singly

# Compile doubly linked list
g++ -o doubly doubly_linked_list.cpp
./doubly

# Compile circular linked list
g++ -o circular circular_linked_list.cpp
./circular

# Compile array-based stack
g++ -o stack_array stack_array.cpp
./stack_array

# Compile linked list-based stack
g++ -o stack_linked_list stack_linked_list.cpp
./stack_linked_list

# Compile array-based queue
g++ -o queue_array queue_array.cpp
./queue_array

# Compile linked list-based queue
g++ -o queue_linked_list queue_linked_list.cpp
./queue_linked_list

# Compile array-based deque
g++ -o deque_array deque_array.cpp
./deque_array

# Compile linked list-based deque
g++ -o deque_linked_list deque_linked_list.cpp
./deque_linked_list
```

### Using clang++:

```bash
clang++ -o singly singly_linked_list.cpp
./singly

clang++ -o stack_array stack_array.cpp
./stack_array
```

## Key Concepts

### Singly Linked List
- Each node has data and a pointer to the next node
- Traversal is only in one direction (forward)
- Last node points to NULL
- Memory efficient but limited traversal

### Doubly Linked List
- Each node has data, pointer to next node, and pointer to previous node
- Traversal in both directions (forward and backward)
- Takes more memory but offers more flexibility
- Better for operations that require backward traversal

### Circular Linked List
- Similar to singly linked list, but last node points back to the first node
- No NULL pointer at the end
- Useful for round-robin scheduling and circular buffers
- Need to be careful with traversal to avoid infinite loops

### Stack (Array-based)
- Uses a fixed-size array to store elements
- Simple and memory-efficient
- Fast operations (O(1) for push, pop, peek)
- Limited by array size (stack overflow)
- **LIFO (Last In, First Out)** principle
- Operations:
  - `push()`: Add element to top - O(1)
  - `pop()`: Remove element from top - O(1)
  - `peek()`: View top element without removing - O(1)
  - `isEmpty()`: Check if stack is empty - O(1)
  - `isFull()`: Check if stack is full - O(1)

### Stack (Linked List-based)
- Uses dynamic memory allocation
- No size limitation (except system memory)
- More flexible than array-based
- Slightly more memory overhead (pointers)
- **LIFO (Last In, First Out)** principle
- Same operations as array-based stack
- All operations are O(1) time complexity

### Queue (Array-based)
- Uses a fixed-size array with circular indexing
- Implements circular queue to avoid wasted space
- Simple and memory-efficient
- Fast operations (O(1) for enqueue, dequeue, peek)
- Limited by array size (queue overflow)
- **FIFO (First In, First Out)** principle
- Operations:
  - `enqueue()`: Add element to rear - O(1)
  - `dequeue()`: Remove element from front - O(1)
  - `peek()`: View front element without removing - O(1)
  - `isEmpty()`: Check if queue is empty - O(1)
  - `isFull()`: Check if queue is full - O(1)

### Queue (Linked List-based)
- Uses dynamic memory allocation
- No size limitation (except system memory)
- More flexible than array-based
- Slightly more memory overhead (pointers)
- **FIFO (First In, First Out)** principle
- Same operations as array-based queue
- All operations are O(1) time complexity
- Uses both front and rear pointers for efficient operations

### Double-ended Queue - Deque (Array-based)
- Uses a fixed-size array with circular indexing
- Allows insertion and deletion at both ends
- More flexible than regular queue
- Fast operations (O(1) for all operations)
- Limited by array size
- Operations:
  - `insertFront()`: Add element at front - O(1)
  - `insertRear()`: Add element at rear - O(1)
  - `deleteFront()`: Remove element from front - O(1)
  - `deleteRear()`: Remove element from rear - O(1)
  - `getFront()`: View front element - O(1)
  - `getRear()`: View rear element - O(1)

### Double-ended Queue - Deque (Linked List-based)
- Uses doubly linked list for bidirectional access
- No size limitation (except system memory)
- Most flexible implementation
- More memory overhead (two pointers per node)
- All operations are O(1) time complexity
- Supports forward and reverse traversal
- Can be used as both stack and queue

## Teaching Tips

### For Linked Lists:

1. Start with **Singly Linked List** as it's the simplest
2. Explain the concept of pointers and dynamic memory allocation
3. Compare and contrast the three types
4. Discuss time and space complexities:
   - Insert/Delete at beginning: O(1)
   - Insert/Delete at end: O(n) for singly, O(1) for doubly (with tail pointer)
   - Search: O(n) for all
5. Discuss use cases for each type

### For Stack:
1. Start with **Array-based Stack** as it's simpler and more intuitive
2. Explain the **LIFO (Last In, First Out)** principle with real-world examples:
   - Stack of plates
   - Undo operations in editors
   - Function call stack
   - Expression evaluation (infix to postfix)
3. Compare **Array-based vs Linked List-based**:
   - Array: Fixed size, faster, memory efficient
   - Linked List: Dynamic size, more flexible, uses more memory
4. Discuss time complexities (all O(1) for basic operations)
5. Explain **Stack Overflow** and **Stack Underflow** errors
6. Show practical applications:
   - Balanced parentheses checking
   - Expression evaluation
   - Infix to Postfix conversion
   - Backtracking algorithms

### For Queue:
1. Start with **Array-based Queue** (circular queue implementation)
2. Explain the **FIFO (First In, First Out)** principle with real-world examples:
   - Queue of people waiting in line
   - Printer job queue
   - CPU scheduling
   - Breadth-First Search (BFS)
3. Explain **Circular Queue** concept to avoid wasted space:
   - Show the problem with linear queue (wasted space)
   - Demonstrate circular indexing with modulo operator
4. Compare **Array-based vs Linked List-based**:
   - Array: Fixed size, faster, memory efficient
   - Linked List: Dynamic size, no overflow, uses more memory
5. Discuss time complexities (all O(1) for basic operations)
6. Explain **Queue Overflow** and **Queue Underflow** errors
7. Show practical applications:
   - BFS in graphs
   - Level-order traversal in trees
   - Buffer management
   - Task scheduling

### For Deque (Double-ended Queue):
1. Introduce Deque as an extension of Queue
2. Explain that Deque allows operations at both ends:
   - Can be used as both Stack and Queue
   - More flexible than regular Queue
3. Compare **Array-based vs Linked List-based**:
   - Array: Fixed size, circular indexing, memory efficient
   - Linked List: Dynamic size, uses doubly linked list, more flexible
4. Discuss use cases:
   - Palindrome checking
   - Sliding window problems
   - Both Stack and Queue operations needed
   - Double-ended priority queue
5. Show that it combines features of both Stack and Queue:
   - Can insert/delete from front (like Stack)
   - Can insert/delete from rear (like Queue)
6. Demonstrate practical applications:
   - Undo/Redo functionality
   - Cache implementation
   - Browser history (forward/backward navigation)

## Memory Management

All implementations use proper memory management:
- Dynamic allocation with `new`
- Proper cleanup in destructors
- No memory leaks
