#include <iostream>
using namespace std;

#define MAX_SIZE 100  // Maximum size of the stack

class Stack {
private:
    int arr[MAX_SIZE];  // Array to store stack elements
    int top;            // Index of the top element
    
public:
    // Constructor
    Stack() {
        top = -1;  // -1 indicates empty stack
    }
    
    // Check if stack is empty
    bool isEmpty() {
        return top == -1;
    }
    
    // Check if stack is full
    bool isFull() {
        return top == MAX_SIZE - 1;
    }
    
    // Push an element onto the stack
    void push(int value) {
        if (isFull()) {
            cout << "Stack Overflow! Cannot push " << value << "\n";
            return;
        }
        
        top++;           // Move top to next position
        arr[top] = value; // Store the value
        cout << "Pushed " << value << " onto the stack\n";
    }
    
    // Pop an element from the stack
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! Cannot pop from empty stack\n";
            return -1;  // Return error value
        }
        
        int value = arr[top];  // Get the top element
        top--;                  // Decrease top
        cout << "Popped " << value << " from the stack\n";
        return value;
    }
    
    // Peek at the top element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty! Cannot peek\n";
            return -1;  // Return error value
        }
        
        return arr[top];
    }
    
    // Get the top element (same as peek, but with message)
    int topElement() {
        if (isEmpty()) {
            cout << "Stack is empty!\n";
            return -1;
        }
        
        cout << "Top element is: " << arr[top] << "\n";
        return arr[top];
    }
    
    // Get the current size of the stack
    int size() {
        return top + 1;
    }
    
    // Display all elements in the stack (from top to bottom)
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }
        
        cout << "Stack (top to bottom): ";
        for (int i = top; i >= 0; i--) {
            cout << arr[i];
            if (i > 0) {
                cout << " <- ";
            }
        }
        cout << "\n";
    }
    
    // Clear the stack
    void clear() {
        top = -1;
        cout << "Stack cleared\n";
    }
};

// Main function for demonstration
int main() {
    Stack stack;
    
    cout << "=== Stack (Array-based) Demonstration ===\n\n";
    
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
    
    // Demonstrate stack overflow (if MAX_SIZE is small)
    cout << "Attempting to push many elements:\n";
    for (int i = 0; i < 95; i++) {
        stack.push(i + 100);
    }
    cout << "Size: " << stack.size() << "\n\n";
    
    // Demonstrate stack underflow
    cout << "Clearing stack and attempting to pop:\n";
    stack.clear();
    stack.pop();
    
    return 0;
}