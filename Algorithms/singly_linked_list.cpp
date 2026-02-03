#include <iostream>
using namespace std;

// Node structure for Singly Linked List
struct Node {
    int data;
    Node* next;  // Pointer to the next node
    
    // Constructor
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;  // Pointer to the first node
    
public:
    // Constructor
    SinglyLinkedList() {
        head = nullptr;
    }
    
    // Destructor - Clean up memory
    ~SinglyLinkedList() {
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
        newNode->next = head;
        head = newNode;
        cout << "Inserted " << value << " at the beginning\n";
    }
    
    // Insert at the end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);
        
        // If list is empty
        if (head == nullptr) {
            head = newNode;
        } else {
            // Traverse to the last node
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
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
        for (int i = 1; i < position - 1 && current != nullptr; i++) {
            current = current->next;
        }
        
        if (current == nullptr) {
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
        
        // If head node contains the value
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted " << value << "\n";
            return;
        }
        
        // Search for the node to delete
        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            cout << "Value " << value << " not found\n";
            return;
        }
        
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
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
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted node at position 1\n";
            return;
        }
        
        Node* current = head;
        for (int i = 1; i < position - 1 && current->next != nullptr; i++) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
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
    
    // Display the list
    void display() {
        if (head == nullptr) {
            cout << "List is empty\n";
            return;
        }
        
        Node* current = head;
        cout << "Singly Linked List: ";
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) {
                cout << " -> ";
            }
            current = current->next;
        }
        cout << " -> NULL\n";
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
        Node* prev = nullptr;
        Node* current = head;
        Node* next = nullptr;
        
        while (current != nullptr) {
            next = current->next;  // Store next node
            current->next = prev;  // Reverse current node's pointer
            prev = current;        // Move prev forward
            current = next;        // Move current forward
        }
        
        head = prev;
        cout << "List reversed\n";
    }
    
    // Swap adjacent nodes pairwise (swap 1-2, 3-4, 5-6, etc.)
    void swapAdjacent() {
        if (head == nullptr || head->next == nullptr) {
            cout << "Not enough nodes to swap (need at least 2 nodes)\n";
            return;
        }
        
        Node* prev = nullptr;
        Node* current = head;
        bool isFirstPair = true;
        
        // Traverse and swap pairs
        while (current != nullptr && current->next != nullptr) {
            Node* next = current->next;      // Second node of the pair
            Node* nextPair = next->next;     // First node of next pair
            
            // Swap the pair: current <-> next
            current->next = nextPair;        // First node now points to next pair
            next->next = current;            // Second node now points to first node
            
            // Update head if this is the first pair
            if (isFirstPair) {
                head = next;
                prev = current;
                isFirstPair = false;
            } else {
                // Link previous swapped pair to current swapped pair
                prev->next = next;
                prev = current;
            }
            
            // Move to the next pair
            current = nextPair;
        }
        
        cout << "Adjacent nodes swapped pairwise\n";
    }
};

// Main function for demonstration
int main() {
    SinglyLinkedList list;
    
    cout << "=== Singly Linked List Demonstration ===\n\n";
    
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
    
    // Reverse operation
    list.reverse();
    list.display();
    cout << "\n";
    
    // Swap adjacent nodes operation
    cout << "Swapping adjacent nodes pairwise:\n";
    list.swapAdjacent();
    list.display();
    
    return 0;
}