/**
 * Problem: Constrained Subsequence Sum
 * Difficulty: Hard
 * Tags: array, dp, queue, heap
 * 
 * Approach: DP with deque - dp[i] = max sum ending at i, use deque to track max in window
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(n) for DP and deque
 */

import java.util.*;

class Solution {
    public int constrainedSubsetSum(int[] nums, int k) {
        int n = nums.length;
        int[] dp = new int[n];
        Deque<Integer> dq = new ArrayDeque<>();
        
        for (int i = 0; i < n; i++) {
            while (!dq.isEmpty() && dq.peekFirst() < i - k) {
                dq.pollFirst();
            }
            
            dp[i] = nums[i];
            if (!dq.isEmpty()) {
                dp[i] = Math.max(dp[i], dp[dq.peekFirst()] + nums[i]);
            }
            
            while (!dq.isEmpty() && dp[dq.peekLast()] <= dp[i]) {
                dq.pollLast();
            }
            
            dq.offerLast(i);
        }
        
        int result = Integer.MIN_VALUE;
        for (int val : dp) {
            result = Math.max(result, val);
        }
        return result;
    }
}