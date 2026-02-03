/**
 * Problem: Number of Recent Calls
 * Difficulty: Easy
 * Tags: queue
 * 
 * Approach: Use deque to maintain calls within [t-3000, t] range
 * Time Complexity: O(1) amortized per ping
 * Space Complexity: O(n) for storing calls
 */

import java.util.*;

class RecentCounter {
    private Queue<Integer> queue;

    public RecentCounter() {
        queue = new LinkedList<>();
    }
    
    public int ping(int t) {
        queue.offer(t);
        while (queue.peek() < t - 3000) {
            queue.poll();
        }
        return queue.size();
    }
}

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter obj = new RecentCounter();
 * int param_1 = obj.ping(t);
 */