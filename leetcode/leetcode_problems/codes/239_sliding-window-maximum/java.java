/**
 * Problem: Sliding Window Maximum
 * Difficulty: Hard
 * Tags: array, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int[] maxSlidingWindow(int[] nums, int k) {
        Deque<Integer> dq = new ArrayDeque<>();
        List<Integer> result = new ArrayList<>();
        
        for (int i = 0; i < nums.length; i++) {
            while (!dq.isEmpty() && dq.peekFirst() < i - k + 1) {
                dq.pollFirst();
            }
            
            while (!dq.isEmpty() && nums[dq.peekLast()] < nums[i]) {
                dq.pollLast();
            }
            
            dq.offerLast(i);
            
            if (i >= k - 1) {
                result.add(nums[dq.peekFirst()]);
            }
        }
        
        return result.stream().mapToInt(i -> i).toArray();
    }
}