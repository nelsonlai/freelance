struct ListNode {
    int val;
    ListNode* next;
    ListNode(int val) : val(val), next(nullptr) {}
};

class MyLinkedList {
private:
    ListNode* head;
    int size;

public:
    MyLinkedList() {
        head = nullptr;
        size = 0;
    }
    
    int get(int index) {
        if (index < 0 || index >= size) {
            return -1;
        }
        ListNode* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->val;
    }
    
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void addAtTail(int val) {
        if (head == nullptr) {
            head = new ListNode(val);
        } else {
            ListNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new ListNode(val);
        }
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index > size) {
            return;
        }
        if (index <= 0) {
            addAtHead(val);
            return;
        }
        ListNode* curr = head;
        for (int i = 0; i < index - 1; i++) {
            curr = curr->next;
        }
        ListNode* newNode = new ListNode(val);
        newNode->next = curr->next;
        curr->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        if (index == 0) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        } else {
            ListNode* curr = head;
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            ListNode* temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        size--;
    }
};
