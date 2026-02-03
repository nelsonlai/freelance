/**
 * Problem: Number of Valid Subarrays
 * Difficulty: Hard
 * Tags: array, stack
 * 
 * Approach: Monotonic stack - count subarrays where first element is minimum
 * Time Complexity: O(n)
 * Space Complexity: O(n) for stack
 */

import java.util.*;

class Solution {
    public int validSubarrays(int[] nums) {
        Stack<Integer> stack = new Stack<>();
        int result = 0;
        
        for (int i = 0; i < nums.length; i++) {
            while (!stack.isEmpty() && nums[stack.peek()] > nums[i]) {
                stack.pop();
            }
            stack.push(i);
            result += stack.size();
        }
        
        return result;
    }
}