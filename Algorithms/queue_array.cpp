#include <iostream>
using namespace std;

#define MAX_SIZE 100  // Maximum size of the queue

class Queue {
private:
    int arr[MAX_SIZE];
    int front;  // Index of the front element
    int rear;   // Index of the rear element
    int count;  // Number of elements in queue
    
public:
    // Constructor
    Queue() {
        front = 0;
        rear = -1;
        count = 0;
    }
    
    // Check if queue is empty
    bool isEmpty() {
        return count == 0;
    }
    
    // Check if queue is full
    bool isFull() {
        return count == MAX_SIZE;
    }
    
    // Enqueue (add) an element to the rear of the queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << value << "\n";
            return;
        }
        
        rear = (rear + 1) % MAX_SIZE;  // Circular increment
        arr[rear] = value;
        count++;
        cout << "Enqueued " << value << " to the queue\n";
    }
    
    // Dequeue (remove) an element from the front of the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! Cannot dequeue from empty queue\n";
            return -1;  // Return error value
        }
        
        int value = arr[front];
        front = (front + 1) % MAX_SIZE;  // Circular increment
        count--;
        cout << "Dequeued " << value << " from the queue\n";
        return value;
    }
    
    // Peek at the front element without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Queue is empty! Cannot peek\n";
            return -1;  // Return error value
        }
        
        return arr[front];
    }
    
    // Get the front element (same as peek, but with message)
    int frontElement() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        
        cout << "Front element is: " << arr[front] << "\n";
        return arr[front];
    }
    
    // Get the rear element
    int rearElement() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return -1;
        }
        
        cout << "Rear element is: " << arr[rear] << "\n";
        return arr[rear];
    }
    
    // Get the current size of the queue
    int size() {
        return count;
    }
    
    // Display all elements in the queue (from front to rear)
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        
        cout << "Queue (front to rear): ";
        int i = front;
        int elements = 0;
        
        while (elements < count) {
            cout << arr[i];
            if (elements < count - 1) {
                cout << " <- ";
            }
            i = (i + 1) % MAX_SIZE;
            elements++;
        }
        cout << "\n";
    }
    
    // Clear the queue
    void clear() {
        front = 0;
        rear = -1;
        count = 0;
        cout << "Queue cleared\n";
    }
};

// Main function for demonstration
int main() {
    Queue queue;
    
    cout << "=== Queue (Array-based) Demonstration ===\n\n";
    
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
    
    // Enqueue more elements (demonstrates circular nature)
    cout << "Enqueueing more elements:\n";
    queue.enqueue(60);
    queue.enqueue(70);
    queue.display();
    cout << "Size: " << queue.size() << "\n\n";
    
    // Demonstrate queue overflow
    cout << "Attempting to enqueue many elements:\n";
    for (int i = 0; i < 95; i++) {
        queue.enqueue(i + 100);
    }
    cout << "Size: " << queue.size() << "\n\n";
    
    // Demonstrate queue underflow
    cout << "Clearing queue and attempting to dequeue:\n";
    queue.clear();
    queue.dequeue();
    
    return 0;
}