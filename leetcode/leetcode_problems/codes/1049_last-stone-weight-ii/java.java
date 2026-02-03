/**
 * Problem: Last Stone Weight II
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: Partition stones into two groups with minimum difference - subset sum problem
 * Time Complexity: O(n * sum(stones))
 * Space Complexity: O(sum(stones))
 */

import java.util.*;

class Solution {
    public int lastStoneWeightII(int[] stones) {
        int total = 0;
        for (int stone : stones) {
            total += stone;
        }
        int target = total / 2;
        Set<Integer> dp = new HashSet<>();
        dp.add(0);
        
        for (int stone : stones) {
            Set<Integer> newDp = new HashSet<>();
            for (int s : dp) {
                if (s + stone <= target) {
                    newDp.add(s + stone);
                }
                newDp.add(s);
            }
            dp = newDp;
        }
        
        int maxSum = 0;
        for (int s : dp) {
            maxSum = Math.max(maxSum, s);
        }
        
        return total - 2 * maxSum;
    }
}