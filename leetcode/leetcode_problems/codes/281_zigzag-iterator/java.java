/**
 * Problem: Zigzag Iterator
 * Difficulty: Medium
 * Tags: array, queue
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

public class ZigzagIterator {
    private Queue<Iterator<Integer>> queue;

    public ZigzagIterator(List<Integer> v1, List<Integer> v2) {
        queue = new LinkedList<>();
        if (!v1.isEmpty()) {
            queue.offer(v1.iterator());
        }
        if (!v2.isEmpty()) {
            queue.offer(v2.iterator());
        }
    }

    public int next() {
        Iterator<Integer> it = queue.poll();
        int val = it.next();
        if (it.hasNext()) {
            queue.offer(it);
        }
        return val;
    }

    public boolean hasNext() {
        return !queue.isEmpty();
    }
}

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i = new ZigzagIterator(v1, v2);
 * while (i.hasNext()) v[f()] = i.next();
 */