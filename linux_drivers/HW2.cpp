#include <iostream>
using namespace std;

class LinkedList {
private:
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;

    // Helper for recursive backward display
    void displayBackward(Node* node) {
        if (!node) return;
        displayBackward(node->next);
        cout << node->data << " ";
    }

public:
    LinkedList() : head(nullptr) {}

    // Helper to append (for testing)
    void append(int val) {
        if (!head) {
            head = new Node(val);
            return;
        }
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = new Node(val);
    }

    // -----------------------------------
    // 1. Insert into sorted list
    // -----------------------------------
    void insertSorted(int value) {
        Node* newNode = new Node(value);

        // Case 1: empty list or insert at front
        if (!head || value < head->data) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* curr = head;
        while (curr->next && curr->next->data < value) {
            curr = curr->next;
        }

        newNode->next = curr->next;
        curr->next = newNode;
    }

    // -----------------------------------
    // 2. Remove duplicates (sorted list)
    // -----------------------------------
    void removeDuplicates() {
        Node* curr = head;

        while (curr && curr->next) {
            if (curr->data == curr->next->data) {
                Node* temp = curr->next;
                curr->next = temp->next;
                delete temp;
            } else {
                curr = curr->next;
            }
        }
    }

    // -----------------------------------
    // 3. Swap nodes by value (not data)
    // -----------------------------------
    void swapNodes(int x, int y) {
        if (x == y) return;

        Node *prevX = nullptr, *currX = head;
        while (currX && currX->data != x) {
            prevX = currX;
            currX = currX->next;
        }

        Node *prevY = nullptr, *currY = head;
        while (currY && currY->data != y) {
            prevY = currY;
            currY = currY->next;
        }

        // If either not found, do nothing
        if (!currX || !currY) return;

        // Fix previous links
        if (prevX) prevX->next = currY;
        else head = currY;

        if (prevY) prevY->next = currX;
        else head = currX;

        // Swap next pointers
        Node* temp = currX->next;
        currX->next = currY->next;
        currY->next = temp;
    }

    // -----------------------------------
    // 4. Bonus: recursive backward display
    // -----------------------------------
    void displayBackwardRecursive() {
        displayBackward(head);
        cout << endl;
    }

    // Print forward (for testing)
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

int main() {
    LinkedList list;

    list.insertSorted(3);
    list.insertSorted(1);
    list.insertSorted(2);
    list.insertSorted(2);
    list.insertSorted(4);

    list.print();              // 1 -> 2 -> 2 -> 3 -> 4 -> NULL

    list.removeDuplicates();
    list.print();              // 1 -> 2 -> 3 -> 4 -> NULL

    list.swapNodes(2, 4);
    list.print();              // 1 -> 4 -> 3 -> 2 -> NULL

    cout << "Backward: ";
    list.displayBackwardRecursive();  // 2 3 4 1
}