/**
 * Problem: Design Circular Queue
 * Difficulty: Medium
 * Tags: array, linked_list, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class MyCircularQueue {
    private int[] queue;
    private int head;
    private int count;
    private int capacity;

    public MyCircularQueue(int k) {
        queue = new int[k];
        head = 0;
        count = 0;
        capacity = k;
    }
    
    public boolean enQueue(int value) {
        if (count == capacity) {
            return false;
        }
        queue[(head + count) % capacity] = value;
        count++;
        return true;
    }
    
    public boolean deQueue() {
        if (count == 0) {
            return false;
        }
        head = (head + 1) % capacity;
        count--;
        return true;
    }
    
    public int Front() {
        if (count == 0) {
            return -1;
        }
        return queue[head];
    }
    
    public int Rear() {
        if (count == 0) {
            return -1;
        }
        return queue[(head + count - 1) % capacity];
    }
    
    public boolean isEmpty() {
        return count == 0;
    }
    
    public boolean isFull() {
        return count == capacity;
    }
}

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue obj = new MyCircularQueue(k);
 * boolean param_1 = obj.enQueue(value);
 * boolean param_2 = obj.deQueue();
 * int param_3 = obj.Front();
 * int param_4 = obj.Rear();
 * boolean param_5 = obj.isEmpty();
 * boolean param_6 = obj.isFull();
 */