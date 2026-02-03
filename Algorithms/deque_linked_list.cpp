#include <iostream>
using namespace std;

// Node structure for Deque using Linked List
struct Node {
    int data;
    Node* next;
    Node* prev;
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class Deque {
private:
    Node* front;  // Pointer to the front of the deque
    Node* rear;   // Pointer to the rear of the deque
    int dequeSize;  // Track the size of the deque
    
public:
    // Constructor
    Deque() {
        front = nullptr;
        rear = nullptr;
        dequeSize = 0;
    }
    
    // Destructor - Clean up memory
    ~Deque() {
        while (!isEmpty()) {
            deleteFront();
        }
    }
    
    // Check if deque is empty
    bool isEmpty() {
        return front == nullptr;
    }
    
    // Insert element at the front
    void insertFront(int value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            // Deque is empty, both front and rear point to new node
            front = rear = newNode;
        } else {
            newNode->next = front;
            front->prev = newNode;
            front = newNode;
        }
        
        dequeSize++;
        cout << "Inserted " << value << " at the front\n";
    }
    
    // Insert element at the rear
    void insertRear(int value) {
        Node* newNode = new Node(value);
        
        if (isEmpty()) {
            // Deque is empty, both front and rear point to new node
            front = rear = newNode;
        } else {
            newNode->prev = rear;
            rear->next = newNode;
            rear = newNode;
        }
        
        dequeSize++;
        cout << "Inserted " << value << " at the rear\n";
    }
    
    // Delete element from the front
    int deleteFront() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from front\n";
            return -1;
        }
        
        Node* temp = front;
        int value = front->data;
        
        if (front == rear) {
            // Only one element
            front = rear = nullptr;
        } else {
            front = front->next;
            front->prev = nullptr;
        }
        
        delete temp;
        dequeSize--;
        cout << "Deleted " << value << " from the front\n";
        return value;
    }
    
    // Delete element from the rear
    int deleteRear() {
        if (isEmpty()) {
            cout << "Deque Underflow! Cannot delete from rear\n";
            return -1;
        }
        
        Node* temp = rear;
        int value = rear->data;
        
        if (front == rear) {
            // Only one element
            front = rear = nullptr;
        } else {
            rear = rear->prev;
            rear->next = nullptr;
        }
        
        delete temp;
        dequeSize--;
        cout << "Deleted " << value << " from the rear\n";
        return value;
    }
    
    // Get the front element
    int getFront() {
        if (isEmpty()) {
            cout << "Deque is empty!\n";
            return -1;
        }
        
        cout << "Front element is: " << front->data << "\n";
        return front->data;
    }
    
    // Get the rear element
    int getRear() {
        if (isEmpty()) {
            cout << "Deque is empty!\n";
            return -1;
        }
        
        cout << "Rear element is: " << rear->data << "\n";
        return rear->data;
    }
    
    // Get the current size of the deque
    int size() {
        return dequeSize;
    }
    
    // Display all elements in the deque (from front to rear)
    void display() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        
        cout << "Deque (front to rear): NULL <-> ";
        Node* current = front;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << " <-> NULL\n";
    }
    
    // Display all elements in the deque (from rear to front)
    void displayReverse() {
        if (isEmpty()) {
            cout << "Deque is empty\n";
            return;
        }
        
        cout << "Deque (rear to front): NULL <-> ";
        Node* current = rear;
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << " <-> NULL\n";
    }
    
    // Clear the deque
    void clear() {
        while (!isEmpty()) {
            deleteFront();
        }
        cout << "Deque cleared\n";
    }
};

// Main function for demonstration
int main() {
    Deque deque;
    
    cout << "=== Double-ended Queue (Deque) - Linked List-based Demonstration ===\n\n";
    
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
    
    // Demonstrate reverse display
    cout << "Displaying in reverse order:\n";
    deque.displayReverse();
    cout << "\n";
    
    // Demonstrate deque underflow
    cout << "Clearing deque and attempting to delete:\n";
    deque.clear();
    deque.deleteFront();
    deque.deleteRear();
    
    return 0;
}