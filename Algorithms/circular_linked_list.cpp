#include <iostream>
using namespace std;

// Node structure for Circular Linked List (Singly)
struct Node {
    int data;
    Node* next;  // Pointer to the next node
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class CircularLinkedList {
private:
    Node* head;  // Pointer to the first node
    
public:
    // Constructor
    CircularLinkedList() {
        head = nullptr;
    }
    
    // Destructor - Clean up memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head->next;
        while (current != head) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        delete head;
    }
    
    // Insert at the beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // List is empty
            head = newNode;
            newNode->next = head;  // Point to itself
        } else {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            newNode->next = head;
            head = newNode;
            last->next = head;  // Update last node's next
        }
        cout << "Inserted " << value << " at the beginning\n";
    }
    
    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            // List is empty
            head = newNode;
            newNode->next = head;
        } else {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            last->next = newNode;
            newNode->next = head;
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
        
        Node* newNode = new Node(value);
        Node* current = head;
        
        // Traverse to the node before the target position
        for (int i = 1; i < position - 1 && current->next != head; i++) {
            current = current->next;
        }
        
        if (current->next == head && position > getSize() + 1) {
            cout << "Position out of range\n";
            delete newNode;
            return;
        }
        
        newNode->next = current->next;
        current->next = newNode;
        cout << "Inserted " << value << " at position " << position << "\n";
    }
    
    // Delete a node by value
    void deleteByValue(int value) {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = head;
        Node* prev = nullptr;
        
        // If head node contains the value
        if (head->data == value) {
            // Find the last node
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            if (head == head->next) {
                // Only one node in the list
                delete head;
                head = nullptr;
            } else {
                head = head->next;
                last->next = head;
                delete current;
            }
            cout << "Deleted " << value << "\n";
            return;
        }
        
        // Search for the node to delete
        prev = head;
        current = head->next;
        
        while (current != head && current->data != value) {
            prev = current;
            current = current->next;
        }
        
        if (current == head) {
            cout << "Value " << value << " not found\n";
            return;
        }
        
        prev->next = current->next;
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
        
        if (position == 1) {
            // Delete head
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            if (head == head->next) {
                // Only one node
                delete head;
                head = nullptr;
            } else {
                Node* temp = head;
                head = head->next;
                last->next = head;
                delete temp;
            }
            cout << "Deleted node at position 1\n";
            return;
        }
        
        Node* current = head;
        for (int i = 1; i < position - 1 && current->next != head; i++) {
            current = current->next;
        }
        
        if (current->next == head) {
            cout << "Position out of range\n";
            return;
        }
        
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Deleted node at position " << position << "\n";
    }
    
    // Search for a value
    bool search(int value) {
        if (head == nullptr) {
            cout << "List is empty\n";
            return false;
        }
        
        Node* current = head;
        int position = 1;
        
        do {
            if (current->data == value) {
                cout << "Value " << value << " found at position " << position << "\n";
                return true;
            }
            current = current->next;
            position++;
        } while (current != head);
        
        cout << "Value " << value << " not found\n";
        return false;
    }
    
    // Display the list
    void display() {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = head;
        cout << "Circular Linked List: ";
        
        do {
            cout << current->data;
            if (current->next != head) {
                cout << " -> ";
            }
            current = current->next;
        } while (current != head);
        
        cout << " -> (back to head: " << head->data << ")\n";
    }
    
    // Get the size of the list
    int getSize() {
        if (head == nullptr) {
            return 0;
        }
        
        int count = 0;
        Node* current = head;
        
        do {
            count++;
            current = current->next;
        } while (current != head);
        
        return count;
    }
    
    // Check if the list is circular (utility function)
    // Floyd's Cycle Detection Algorithm
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    bool isCircular() {
        if (head == nullptr) {
            return true;
        }
        
        Node* slow = head;
        Node* fast = head;
        
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            
            if (slow == fast) {
                return true;
            }
        }
        
        return false;
    }
};

// Main function for demonstration
int main() {
    CircularLinkedList list;
    
    cout << "=== Circular Linked List Demonstration ===\n\n";
    
    // Insert operations
    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtBeginning(5);
    list.insertAtPosition(15, 3);
    list.display();
    cout << "Size: " << list.getSize() << "\n\n";
    
    // Search operation
    list.search(20);
    list.search(100);
    cout << "\n";
    
    // Delete operations
    list.deleteByValue(15);
    list.display();
    
    list.deleteAtPosition(2);
    list.display();
    cout << "\n";
    
    // Demonstrate circular nature
    cout << "Displaying list twice to show circular nature:\n";
    list.display();
    list.display();
    
    return 0;
}