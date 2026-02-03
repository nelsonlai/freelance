/**
 * Problem: Jump Game VII
 * Difficulty: Medium
 * Tags: array, string, dp, sliding window
 * 
 * Approach: DP with sliding window to track reachable positions
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public boolean canReach(String s, int minJump, int maxJump) {
        int n = s.length();
        if (s.charAt(n - 1) == '1') {
            return false;
        }
        
        boolean[] dp = new boolean[n];
        dp[0] = true;
        Deque<Integer> queue = new ArrayDeque<>();
        queue.offer(0);
        
        for (int i = 1; i < n; i++) {
            while (!queue.isEmpty() && queue.peekFirst() < i - maxJump) {
                queue.pollFirst();
            }
            
            if (s.charAt(i) == '0' && !queue.isEmpty() && queue.peekFirst() <= i - minJump) {
                dp[i] = true;
                queue.offerLast(i);
            }
        }
        
        return dp[n - 1];
    }
}