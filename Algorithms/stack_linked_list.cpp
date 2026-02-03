#include <iostream>
using namespace std;

// Node structure for Stack using Linked List
struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Stack {
private:
    Node* top;  // Pointer to the top of the stack
    int stackSize;  // Track the size of the stack
    
public:
    // Constructor
    Stack() {
        top = nullptr;
        stackSize = 0;
    }
    
    // Destructor - Clean up memory
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return top == nullptr;
    }
    
    // Push an element onto the stack
    void push(int value) {
        Node* newNode = new Node(value);
        
        // If stack is empty, new node becomes top
        // Otherwise, new node points to current top, then becomes new top
        if (isEmpty()) {
            top = newNode;
        } else {
            newNode->next = top;
            top = newNode;
        }
        
        stackSize++;
        cout << "Pushed " << value << " onto the stack\n";
    }
    
    // Pop an element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop from empty stack\n";
            return -1;  // Return error value
        }
        
        Node* temp = top;        // Store current top
        int value = top->data;   // Get the data
        top = top->next;         // Move top to next node
        delete temp;             // Free memory
        stackSize--;
        
        cout << "Popped " << value << " from the stack\n";
        return value;
    }
    
    // Peek at the top element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot peek\n";
            return -1;  // Return error value
        }
        
        return top->data;
    }
    
    // Get the top element (same as peek, but with message)
    int topElement() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        
        cout << "Top element is: " << top->data << "\n";
        return top->data;
    }
    
    // Get the current size of the stack
    int size() {
        return stackSize;
    }
    
    // Display all elements in the stack (from top to bottom)
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        
        cout << "Stack (top to bottom): ";
        Node* current = top;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL\n";
    }
    
    // Clear the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
        cout << "Stack cleared\n";
    }
};

// Main function for demonstration
int main() {
    Stack stack;
    
    cout << "=== Stack (Linked List-based) Demonstration ===\n\n";
    
    // Check initial state
    cout << "Initial state:\n";
    cout << "Is empty: " << (stack.isEmpty() ? "Yes" : "No") << "\n";
    cout << "Size: " << stack.size() << "\n\n";
    
    // Push operations
    cout << "Pushing elements:\n";
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    stack.display();
    cout << "Size: " << stack.size() << "\n\n";
    
    // Peek operation
    cout << "Peek operation:\n";
    stack.topElement();
    cout << "\n";
    
    // Pop operations
    cout << "Popping elements:\n";
    stack.pop();
    stack.display();
    cout << "Size: " << stack.size() << "\n\n";
    
    stack.pop();
    stack.display();
    cout << "\n";
    
    // Peek after pops
    cout << "Top element after pops: ";
    stack.topElement();
    cout << "\n";
    
    // Push more elements
    cout << "Pushing more elements:\n";
    stack.push(60);
    stack.push(70);
    stack.display();
    cout << "Size: " << stack.size() << "\n\n";
    
    // Demonstrate stack underflow
    cout << "Clearing stack and attempting to pop:\n";
    stack.clear();
    stack.pop();
    
    return 0;
}