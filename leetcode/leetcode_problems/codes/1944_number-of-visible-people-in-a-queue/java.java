/**
 * Problem: Number of Visible People in a Queue
 * Difficulty: Hard
 * Tags: array, stack, monotonic stack
 * 
 * Approach: Monotonic stack - count people visible to the right
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] canSeePersonsCount(int[] heights) {
        int n = heights.length;
        int[] result = new int[n];
        Stack<Integer> stack = new Stack<>();
        
        for (int i = n - 1; i >= 0; i--) {
            int count = 0;
            while (!stack.isEmpty() && heights[stack.peek()] < heights[i]) {
                stack.pop();
                count++;
            }
            
            if (!stack.isEmpty()) {
                count++;
            }
            
            result[i] = count;
            stack.push(i);
        }
        
        return result;
    }
}