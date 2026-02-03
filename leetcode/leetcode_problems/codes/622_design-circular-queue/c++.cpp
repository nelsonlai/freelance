/*
 * Problem: Design Circular Queue
 * Difficulty: Medium
 * Tags: array, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class MyCircularQueue {
private:
    vector<int> queue;
    int head;
    int count;
    int capacity;

public:
    MyCircularQueue(int k) {
        queue.resize(k);
        head = 0;
        count = 0;
        capacity = k;
    }
    
    bool enQueue(int value) {
        if (count == capacity) {
            return false;
        }
        queue[(head + count) % capacity] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if (count == 0) {
            return false;
        }
        head = (head + 1) % capacity;
        count--;
        return true;
    }
    
    int Front() {
        if (count == 0) {
            return -1;
        }
        return queue[head];
    }
    
    int Rear() {
        if (count == 0) {
            return -1;
        }
        return queue[(head + count - 1) % capacity];
    }
    
    bool isEmpty() {
        return count == 0;
    }
    
    bool isFull() {
        return count == capacity;
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */