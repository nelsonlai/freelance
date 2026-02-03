/*
 * Problem: Design Circular Deque
 * Difficulty: Medium
 * Tags: array, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class MyCircularDeque {
private:
    vector<int> queue;
    int head;
    int count;
    int capacity;

public:
    MyCircularDeque(int k) {
        queue.resize(k);
        head = 0;
        count = 0;
        capacity = k;
    }
    
    bool insertFront(int value) {
        if (count == capacity) {
            return false;
        }
        head = (head - 1 + capacity) % capacity;
        queue[head] = value;
        count++;
        return true;
    }
    
    bool insertLast(int value) {
        if (count == capacity) {
            return false;
        }
        int tail = (head + count) % capacity;
        queue[tail] = value;
        count++;
        return true;
    }
    
    bool deleteFront() {
        if (count == 0) {
            return false;
        }
        head = (head + 1) % capacity;
        count--;
        return true;
    }
    
    bool deleteLast() {
        if (count == 0) {
            return false;
        }
        count--;
        return true;
    }
    
    int getFront() {
        if (count == 0) {
            return -1;
        }
        return queue[head];
    }
    
    int getRear() {
        if (count == 0) {
            return -1;
        }
        int tail = (head + count - 1) % capacity;
        return queue[tail];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */