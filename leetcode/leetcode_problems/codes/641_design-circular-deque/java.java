/**
 * Problem: Design Circular Deque
 * Difficulty: Medium
 * Tags: array, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class MyCircularDeque {
    private int[] queue;
    private int head;
    private int count;
    private int capacity;

    public MyCircularDeque(int k) {
        queue = new int[k];
        head = 0;
        count = 0;
        capacity = k;
    }
    
    public boolean insertFront(int value) {
        if (count == capacity) {
            return false;
        }
        head = (head - 1 + capacity) % capacity;
        queue[head] = value;
        count++;
        return true;
    }
    
    public boolean insertLast(int value) {
        if (count == capacity) {
            return false;
        }
        int tail = (head + count) % capacity;
        queue[tail] = value;
        count++;
        return true;
    }
    
    public boolean deleteFront() {
        if (count == 0) {
            return false;
        }
        head = (head + 1) % capacity;
        count--;
        return true;
    }
    
    public boolean deleteLast() {
        if (count == 0) {
            return false;
        }
        count--;
        return true;
    }
    
    public int getFront() {
        if (count == 0) {
            return -1;
        }
        return queue[head];
    }
    
    public int getRear() {
        if (count == 0) {
            return -1;
        }
        int tail = (head + count - 1) % capacity;
        return queue[tail];
    }
    
    public boolean isEmpty() {
        return count == 0;
    }
    
    public boolean isFull() {
        return count == capacity;
    }
}

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque obj = new MyCircularDeque(k);
 * boolean param_1 = obj.insertFront(value);
 * boolean param_2 = obj.insertLast(value);
 * boolean param_3 = obj.deleteFront();
 * boolean param_4 = obj.deleteLast();
 * int param_5 = obj.getFront();
 * int param_6 = obj.getRear();
 * boolean param_7 = obj.isEmpty();
 * boolean param_8 = obj.isFull();
 */