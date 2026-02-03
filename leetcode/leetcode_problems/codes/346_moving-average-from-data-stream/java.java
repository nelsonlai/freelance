/**
 * Problem: Moving Average from Data Stream
 * Difficulty: Easy
 * Tags: array, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class MovingAverage {
    private int size;
    private Queue<Integer> queue;
    private double sum;

    public MovingAverage(int size) {
        this.size = size;
        this.queue = new LinkedList<>();
        this.sum = 0;
    }
    
    public double next(int val) {
        queue.offer(val);
        sum += val;
        if (queue.size() > size) {
            sum -= queue.poll();
        }
        return sum / queue.size();
    }
}

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage obj = new MovingAverage(size);
 * double param_1 = obj.next(val);
 */