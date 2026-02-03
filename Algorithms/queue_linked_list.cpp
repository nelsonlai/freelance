#include <iostream>
using namespace std;

// Node structure for Queue using Linked List
struct Node {
    int data;
    Node* next;
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;  // Pointer to the front of the queue
    Node* rear;   // Pointer to the rear of the queue
    int queueSize;  // Track the size of the queue
    
public:
    // Constructor
    Queue() {
        front = nullptr;
        rear = nullptr;
        queueSize = 0;
    }
    
    // Destructor - Clean up memory
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    // Check if queue is empty
    bool isEmpty() {
        return front == nullptr;
    }
    
    // Enqueue (add) an element to the rear of the queue
    void enqueue(int value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            // Queue is empty, both front and rear point to new node
            front = rear = newNode;
        } else {
            // Add new node at the rear and update rear pointer
            rear->next = newNode;
            rear = newNode;
        }
        
        queueSize++;
        cout << "Enqueued " << value << " to the queue\n";
    }
    
    // Dequeue (remove) an element from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Cannot dequeue from empty queue\n";
            return -1;  // Return error value
        }
        
        Node* temp = front;        // Store current front
        int value = front->data;   // Get the data
        front = front->next;       // Move front to next node
        
        // If queue becomes empty, update rear to nullptr
        if (front == nullptr) {
            rear = nullptr;
        }
        
        delete temp;  // Free memory
        queueSize--;
        
        cout << "Dequeued " << value << " from the queue\n";
        return value;
    }
    
    // Peek at the front element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot peek\n";
            return -1;  // Return error value
        }
        
        return front->data;
    }
    
    // Get the front element (same as peek, but with message)
    int frontElement() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        
        cout << "Front element is: " << front->data << "\n";
        return front->data;
    }
    
    // Get the rear element
    int rearElement() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        
        cout << "Rear element is: " << rear->data << "\n";
        return rear->data;
    }
    
    // Get the current size of the queue
    int size() {
        return queueSize;
    }
    
    // Display all elements in the queue (from front to rear)
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        
        cout << "Queue (front to rear): ";
        Node* current = front;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <- ";
            }
            current = current->next;
        }
        cout << " -> NULL\n";
    }
    
    // Clear the queue
    void clear() {
        while (!isEmpty()) {
            dequeue();
        }
        cout << "Queue cleared\n";
    }
};

// Main function for demonstration
int main() {
    Queue queue;
    
    cout << "=== Queue (Linked List-based) Demonstration ===\n\n";
    
    // Check initial state
    cout << "Initial state:\n";
    cout << "Is empty: " << (queue.isEmpty() ? "Yes" : "No") << "\n";
    cout << "Size: " << queue.size() << "\n\n";
    
    // Enqueue operations
    cout << "Enqueueing elements:\n";
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    queue.display();
    cout << "Size: " << queue.size() << "\n\n";
    
    // Peek operations
    cout << "Peek operations:\n";
    queue.frontElement();
    queue.rearElement();
    cout << "\n";
    
    // Dequeue operations
    cout << "Dequeueing elements:\n";
    queue.dequeue();
    queue.display();
    cout << "Size: " << queue.size() << "\n\n";
    
    queue.dequeue();
    queue.display();
    cout << "\n";
    
    // Peek after dequeues
    cout << "Front and rear elements after dequeues:\n";
    queue.frontElement();
    queue.rearElement();
    cout << "\n";
    
    // Enqueue more elements
    cout << "Enqueueing more elements:\n";
    queue.enqueue(60);
    queue.enqueue(70);
    queue.display();
    cout << "Size: " << queue.size() << "\n\n";
    
    cout << "Attempting to enqueue many elements:\n";
    for (int i = 0; i < 200; i++) {
        queue.enqueue(i + 100);
    }
    queue.display();
    cout << "Size: " << queue.size() << "\n\n";
    
    // Demonstrate queue underflow
    cout << "Clearing queue and attempting to dequeue:\n";
    queue.clear();
    queue.dequeue();
    
    return 0;
}