/**
 * Problem: Design Hit Counter
 * Difficulty: Medium
 * Tags: array, search, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class HitCounter {
    private Queue<Integer> hits;

    public HitCounter() {
        hits = new LinkedList<>();
    }
    
    public void hit(int timestamp) {
        hits.offer(timestamp);
    }
    
    public int getHits(int timestamp) {
        while (!hits.isEmpty() && hits.peek() <= timestamp - 300) {
            hits.poll();
        }
        return hits.size();
    }
}

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter obj = new HitCounter();
 * obj.hit(timestamp);
 * int param_2 = obj.getHits(timestamp);
 */