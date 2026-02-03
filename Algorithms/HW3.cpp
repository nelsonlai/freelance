/*
Homework 3 — Circular Linked List Challenge (Advanced Thinking)

Goal: Build real understanding of circular structures.

Tasks:

Add:

void splitIntoTwo();


Split the circular list into two circular lists

If odd number of nodes, first list gets one extra

Add:

int josephusProblem(int k);


Simulate Josephus elimination:

Every k-th person is removed

Return the survivor

Must use your circular list

Add:

bool isCircular();


Detect whether the list is truly circular

Should return false if structure is broken

Bonus:

Make the circular list support both:

Head-only design

Tail-only design
*/
#include <iostream>
#include <utility> // for std::pair
using namespace std;

class CircularLinkedList {
    private:
        struct Node {
            int data;
            Node* next;
            Node(int d) : data(d), next(nullptr) {}
        };
    
        Node* head;
        Node* tail;
    public:
        enum Mode { HEAD_ONLY, TAIL_ONLY};
        Mode mode;

        CircularLinkedList(Mode m = HEAD_ONLY) {
            mode = m;
            head = nullptr;
            tail = nullptr;
        }

        // -------- Utility Functions --------
        Node* getHead() {
            if (mode == HEAD_ONLY) return head;
            if (!tail) return nullptr;
            return tail->next;
        }

        Node* getTail() {
            if (mode == TAIL_ONLY) return tail;
            if (!head) return nullptr;
            Node* cur = head;
            while (cur->next != head) cur = cur->next;
            return cur;
        }

        // ----- Insert -----
        void insert(int value) {
            Node* newNode = new Node(value);

            if (!head && !tail) {
                head = tail = newNode;
                newNode->next = newNode;
                return;
            }

            if (mode == HEAD_ONLY) {
                Node* t = getTail();
                newNode->next = head;
                t->next = newNode;
                head = newNode;
            }
            else {
                newNode->next = tail->next;
                tail->next = newNode;
                tail = newNode;
            }
        }

        // ----- Display -----
        void display() {
            Node* start = getHead();
            if (!start) {
                cout << "List is empty\n";
                return;
            }

            Node* cur = start;
            do {
                cout << cur->data << " -> ";
                cur = cur->next;
            } while (cur != start);
            cout << endl;
        }

        // ----- isCircular -----
        bool isCircular() {
            Node* start = getHead();
            if (!start) return false;

            Node* slow = start;
            Node* fast = start;

            while ( fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;

                if (slow == fast) return true;
            }
            return false;
        }

        // ----- splitIntoTwo -----
        pair<CircularLinkedList, CircularLinkedList> splitIntoTwo() {
            CircularLinkedList first(mode), second(mode);

            Node* start = getHead();
            if (!start) return {first, second};
            if (start->next == start) {
                first.insert(start->data);
                return {first, second};
            }

            Node* slow = start;
            Node* fast = start;

            while (fast->next != start && fast->next->next != start) {
                slow = slow->next;
                fast = fast->next->next;
            }
            Node* head1 = start;
            Node* head2 = slow->next;

            slow->next = start;

            Node* temp = head2;
            while (temp->next != start) temp = temp->next;
            temp->next = head2;

            // build lists
            Node* cur = head1;
            do { first.insert(cur->data); cur = cur->next; } while (cur != head1);

            cur = head2;
            do { second.insert(cur->data); cur = cur->next; } while (cur != head2);
            
            return {first, second};

        }

        // ----- JosephusProblem -----
        int josephusProblem(int k) {
            Node* start = getHead();
            if (!start) return -1;

            Node* prev = getTail();
            Node* cur = start;
            while (cur->next != cur) {
                for (int i = 1; i < k; i++) {
                    prev = cur;
                    cur = cur->next;
                }

                // remove cur
                prev->next = cur->next;
                delete cur;
                cur = prev->next;
            }

            return cur->data;
        }
};

int main() {

    CircularLinkedList list(CircularLinkedList::TAIL_ONLY);

    for (int i = 1; i <= 7; i++) list.insert(i);

    list.display();

    cout << "Is Circular: " << list.isCircular() << endl;

    auto parts = list.splitIntoTwo(); // C++11/14 compatible (no structured bindings)
    cout << "List A: "; parts.first.display();
    cout << "List B: "; parts.second.display();

    cout << "Josephus Problem survivor(k=3): " << list.josephusProblem(3) << endl;

    return 0;
}