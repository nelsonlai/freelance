/**
 * Problem: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit
 * Difficulty: Medium
 * Tags: array, queue, heap
 * 
 * Approach: Sliding window with two deques to track min and max
 * Time Complexity: O(n) where n is length of nums
 * Space Complexity: O(n) for deques
 */

import java.util.*;

class Solution {
    public int longestSubarray(int[] nums, int limit) {
        Deque<Integer> minDeque = new ArrayDeque<>();
        Deque<Integer> maxDeque = new ArrayDeque<>();
        int left = 0;
        int maxLen = 0;
        
        for (int right = 0; right < nums.length; right++) {
            while (!minDeque.isEmpty() && nums[minDeque.peekLast()] >= nums[right]) {
                minDeque.pollLast();
            }
            minDeque.offerLast(right);
            
            while (!maxDeque.isEmpty() && nums[maxDeque.peekLast()] <= nums[right]) {
                maxDeque.pollLast();
            }
            maxDeque.offerLast(right);
            
            while (nums[maxDeque.peekFirst()] - nums[minDeque.peekFirst()] > limit) {
                if (minDeque.peekFirst() == left) {
                    minDeque.pollFirst();
                }
                if (maxDeque.peekFirst() == left) {
                    maxDeque.pollFirst();
                }
                left++;
            }
            
            maxLen = Math.max(maxLen, right - left + 1);
        }
        
        return maxLen;
    }
}