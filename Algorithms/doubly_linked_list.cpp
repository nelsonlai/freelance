#include <iostream>
using namespace std;

// Node structure for Doubly Linked List
struct Node {
    int data;
    Node* next;  // Pointer to the next node
    Node* prev;  // Pointer to the previous node
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    Node* head;  // Pointer to the first node
    Node* tail;  // Pointer to the last node
    
public:
    // Constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    
    // Destructor - Clean up memory
    ~DoublyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
    
    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // List is empty
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << "Inserted " << value << " at the beginning\n";
    }
    
    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        if (tail == nullptr) {
            // List is empty
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Inserted " << value << " at the end\n";
    }
    
    // Insert at a specific position
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Invalid position\n";
            return;
        }
        
        if (position == 1) {
            insertAtBeginning(value);
            return;
        }
        
        Node* current = head;
        int currentPos = 1;
        
        // Traverse to the node at the target position
        while (current != nullptr && currentPos < position) {
            current = current->next;
            currentPos++;
        }
        
        if (current == nullptr && currentPos < position) {
            // Position is beyond the end, insert at the end
            insertAtEnd(value);
            return;
        }
        
        if (current == nullptr) {
            // This shouldn't happen, but handle it
            cout << "Position out of range\n";
            return;
        }
        
        Node* newNode = new Node(value);
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
        cout << "Inserted " << value << " at position " << position << "\n";
    }
    
    // Delete a node by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = head;
        
        // Search for the node
        while (current != nullptr && current->data != value) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Value " << value << " not found\n";
            return;
        }
        
        // Update pointers
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            // Deleting head
            head = current->next;
        }
        
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            // Deleting tail
            tail = current->prev;
        }
        
        delete current;
        cout << "Deleted " << value << "\n";
    }
    
    // Delete at a specific position
    void deleteAtPosition(int position) {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        if (position < 1) {
            cout << "Invalid position\n";
            return;
        }
        
        Node* current = head;
        int currentPos = 1;
        
        // Traverse to the node at the target position
        while (current != nullptr && currentPos < position) {
            current = current->next;
            currentPos++;
        }
        
        if (current == nullptr) {
            cout << "Position out of range\n";
            return;
        }
        
        // Update pointers
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        
        delete current;
        cout << "Deleted node at position " << position << "\n";
    }
    
    // Search for a value (can search from both directions)
    bool search(int value) {
        // Search from head to tail
        Node* current = head;
        int position = 1;
        
        while (current != nullptr) {
            if (current->data == value) {
                cout << "Value " << value << " found at position " << position << "\n";
                return true;
            }
            current = current->next;
            position++;
        }
        
        cout << "Value " << value << " not found\n";
        return false;
    }
    
    // Display the list forward
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = head;
        cout << "Doubly Linked List (Forward): NULL <-> ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " <-> ";
            }
            current = current->next;
        }
        cout << " <-> NULL\n";
    }
    
    // Display the list backward
    void displayBackward() {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = tail;
        cout << "Doubly Linked List (Backward): NULL <-> ";
        while (current != nullptr) {
            cout << current->data;
            if (current->prev != nullptr) {
                cout << " <-> ";
            }
            current = current->prev;
        }
        cout << " <-> NULL\n";
    }
    
    // Get the size of the list
    int getSize() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    // Reverse the linked list
    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
        
        // Swap next and prev for all nodes
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;  // Move to next node (which is now in prev)
        }
        
        // Swap head and tail
        if (temp != nullptr) {
            tail = head;
            head = temp->prev;
        }
        
        cout << "List reversed\n";
    }
};

// Main function for demonstration
int main() {
    DoublyLinkedList list;
    
    cout << "=== Doubly Linked List Demonstration ===\n\n";
    
    // Insert operations
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);
    list.insertAtPosition(15, 3);
    list.displayForward();
    list.displayBackward();
    cout << "Size: " << list.getSize() << "\n\n";
    
    // Search operation
    list.search(20);
    list.search(100);
    cout << "\n";
    
    // Delete operations
    list.deleteByValue(15);
    list.displayForward();
    
    list.deleteAtPosition(2);
    list.displayForward();
    cout << "\n";
    
    // Reverse operation
    list.reverse();
    list.displayForward();
    list.displayBackward();
    
    return 0;
}