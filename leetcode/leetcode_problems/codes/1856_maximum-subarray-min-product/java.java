/**
 * Problem: Maximum Subarray Min-Product
 * Difficulty: Medium
 * Tags: array, stack, prefix sum
 * 
 * Approach: Use monotonic stack to find left/right boundaries, prefix sum for range sum
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int maxSumMinProduct(int[] nums) {
        int n = nums.length;
        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        int[] left = new int[n];
        Stack<Integer> stack = new Stack<>();
        
        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            left[i] = stack.isEmpty() ? 0 : stack.peek() + 1;
            stack.push(i);
        }
        
        int[] right = new int[n];
        stack.clear();
        
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.isEmpty() && nums[stack.peek()] >= nums[i]) {
                stack.pop();
            }
            right[i] = stack.isEmpty() ? n - 1 : stack.peek() - 1;
            stack.push(i);
        }
        
        long result = 0;
        for (int i = 0; i < n; i++) {
            long total = prefix[right[i] + 1] - prefix[left[i]];
            result = Math.max(result, nums[i] * total);
        }
        
        return (int)(result % 1000000007);
    }
}