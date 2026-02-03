/**
 * Problem: Max Value of Equation
 * Difficulty: Hard
 * Tags: array, sort, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int findMaxValueOfEquation(int[][] points, int k) {
        Deque<int[]> dq = new ArrayDeque<>();
        int maxValue = Integer.MIN_VALUE;
        
        for (int[] point : points) {
            int x = point[0];
            int y = point[1];
            
            while (!dq.isEmpty() && x - dq.peekFirst()[1] > k) {
                dq.pollFirst();
            }
            
            if (!dq.isEmpty()) {
                maxValue = Math.max(maxValue, x + y + dq.peekFirst()[0]);
            }
            
            while (!dq.isEmpty() && dq.peekLast()[0] <= y - x) {
                dq.pollLast();
            }
            
            dq.offerLast(new int[]{y - x, x});
        }
        
        return maxValue;
    }
}