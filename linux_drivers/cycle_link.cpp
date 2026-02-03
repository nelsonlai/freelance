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

public:
    LinkedList() : head(nullptr) {}

    // Add node at end (helper for testing)
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
    // 1. Find Middle using fast/slow
    // -----------------------------------
    int findMiddle() {
        if (!head) {
            cout << "Error: List is empty" << endl;
            return -1;
        }

        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow->data;
    }

    // -----------------------------------
    // 2. Reverse list in-place
    // -----------------------------------
    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        Node* next = nullptr;

        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head = prev;
    }

    // -----------------------------------
    // 3. Detect cycle (Floyd’s algorithm)
    // -----------------------------------
    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }

        return false;
    }

    // Print list (for testing)
    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
}

int main() {
    LinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);
    list.append(40);
    list.append(50);

    list.print();  // 10 -> 20 -> 30 -> 40 -> 50 -> NULL

    cout << "Middle: " << list.findMiddle() << endl; // 30

    list.reverse();
    list.print();  // 50 -> 40 -> 30 -> 20 -> 10 -> NULL

    cout << "Has cycle? " << list.hasCycle() << endl; // false

    return 0;
}
