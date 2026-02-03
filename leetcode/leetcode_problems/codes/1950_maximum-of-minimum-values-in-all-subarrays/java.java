/**
 * Problem: Maximum of Minimum Values in All Subarrays
 * Difficulty: Medium
 * Tags: array, stack, monotonic stack
 * 
 * Approach: For each element, find range where it's minimum, update result for that length
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] findMaximums(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int[] left = new int[n];
        int[] right = new int[n];
        Arrays.fill(left, -1);
        Arrays.fill(right, n);
        Stack<Integer> stack = new Stack<>();
        
        // Find left boundaries
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            if (!stack.isEmpty()) {
                left[i] = stack.peek();
            }
            stack.push(i);
        }
        
        stack.clear();
        // Find right boundaries
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            if (!stack.isEmpty()) {
                right[i] = stack.peek();
            }
            stack.push(i);
        }
        
        // Update result
        for (int i = 0; i < n; i++) {
            int length = right[i] - left[i] - 1;
            result[length - 1] = Math.max(result[length - 1], nums[i]);
        }
        
        // Fill gaps
        for (int i = n - 2; i >= 0; i--) {
            result[i] = Math.max(result[i], result[i + 1]);
        }
        
        return result;
    }
}