#include <iostream>
using namespace std;

#define MAX_SIZE 100  // Maximum size of the deque

class Deque {
private:
    int arr[MAX_SIZE];
    int front;  // Index of the front element
    int rear;   // Index of the rear element
    int count;  // Number of elements in deque
    
public:
    // Constructor
    Deque() {
        front = -1;
        rear = 0;
        count = 0;
    }
    
    // Check if deque is empty
    bool isEmpty() {
        return count == 0;
    }
    
    // Check if deque is full
    bool isFull() {
        return count == MAX_SIZE;
    }
    
    // Insert element at the front
    void insertFront(int value) {
        if (isFull()) {
            cout << "Deque Overflow! Cannot insert " << value << " at front\n";
            return;
        }
        
        if (isEmpty()) {
            // First element
            front = rear = 0;
        } else {
            front = (front - 1 + MAX_SIZE) % MAX_SIZE;  // Circular decrement
        }
        
        arr[front] = value;
        count++;
        cout << "Inserted " << value << " at the front\n";
    }
    
    // Insert element at the rear
    void insertRear(int value) {
        if (isFull()) {
            cout << "Deque Overflow! Cannot insert " << value << " at rear\n";
            return;
        }
        
        if (isEmpty()) {
            // First element
            front = rear = 0;
        } else {
            rear = (rear + 1) % MAX_SIZE;  // Circular increment
        }
        
        arr[rear] = value;
        count++;
        cout << "Inserted " << value << " at the rear\n";
    }
    
    // Delete element from the front
    int deleteFront() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from front\n";
            return -1;
        }
        
        int value = arr[front];
        
        if (front == rear) {
            // Only one element
            front = -1;
            rear = 0;
        } else {
            front = (front + 1) % MAX_SIZE;  // Circular increment
        }
        
        count--;
        cout << "Deleted " << value << " from the front\n";
        return value;
    }
    
    // Delete element from the rear
    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from rear\n";
            return -1;
        }
        
        int value = arr[rear];
        
        if (front == rear) {
            // Only one element
            front = -1;
            rear = 0;
        } else {
            rear = (rear - 1 + MAX_SIZE) % MAX_SIZE;  // Circular decrement
        }
        
        count--;
        cout << "Deleted " << value << " from the rear\n";
        return value;
    }
    
    // Get the front element
    int getFront() {
        if (isEmpty()) {
            cout << "Deque is empty!\n";
            return -1;
        }
        
        cout << "Front element is: " << arr[front] << "\n";
        return arr[front];
    }
    
    // Get the rear element
    int getRear() {
        if (isEmpty()) {
            cout << "Deque is empty!\n";
            return -1;
        }
        
        cout << "Rear element is: " << arr[rear] << "\n";
        return arr[rear];
    }
    
    // Get the current size of the deque
    int size() {
        return count;
    }
    
    // Display all elements in the deque (from front to rear)
    void display() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        
        cout << "Deque (front to rear): ";
        int i = front;
        int elements = 0;
        
        while (elements < count) {
            cout << arr[i];
            if (elements < count - 1) {
                cout << " <-> ";
            }
            i = (i + 1) % MAX_SIZE;
            elements++;
        }
        cout << "\n";
    }
    
    // Clear the deque
    void clear() {
        front = -1;
        rear = 0;
        count = 0;
        cout << "Deque cleared\n";
    }
};

// Main function for demonstration
int main() {
    Deque deque;
    
    cout << "=== Double-ended Queue (Deque) - Array-based Demonstration ===\n\n";
    
    // Check initial state
    cout << "Initial state:\n";
    cout << "Is empty: " << (deque.isEmpty() ? "Yes" : "No") << "\n";
    cout << "Size: " << deque.size() << "\n\n";
    
    // Insert operations at rear (like a queue)
    cout << "Inserting elements at rear (enqueue-like):\n";
    deque.insertRear(10);
    deque.insertRear(20);
    deque.insertRear(30);
    deque.display();
    cout << "Size: " << deque.size() << "\n\n";
    
    // Insert operations at front (unlike a regular queue)
    cout << "Inserting elements at front:\n";
    deque.insertFront(5);
    deque.insertFront(1);
    deque.display();
    cout << "Size: " << deque.size() << "\n\n";
    
    // Peek operations
    cout << "Peek operations:\n";
    deque.getFront();
    deque.getRear();
    cout << "\n";
    
    // Delete operations from rear
    cout << "Deleting from rear:\n";
    deque.deleteRear();
    deque.display();
    cout << "Size: " << deque.size() << "\n\n";
    
    // Delete operations from front
    cout << "Deleting from front:\n";
    deque.deleteFront();
    deque.display();
    cout << "Size: " << deque.size() << "\n\n";
    
    // Peek after deletions
    cout << "Front and rear elements after deletions:\n";
    deque.getFront();
    deque.getRear();
    cout << "\n";
    
    // Demonstrate various insertions
    cout << "Demonstrating flexible insertions:\n";
    deque.insertFront(2);
    deque.insertRear(40);
    deque.insertFront(0);
    deque.display();
    cout << "Size: " << deque.size() << "\n\n";
    
    // Demonstrate deque underflow
    cout << "Clearing deque and attempting to delete:\n";
    deque.clear();
    deque.deleteFront();
    deque.deleteRear();
    
    return 0;
}