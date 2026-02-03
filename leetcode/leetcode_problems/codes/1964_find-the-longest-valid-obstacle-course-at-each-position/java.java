/**
 * Problem: Find the Longest Valid Obstacle Course at Each Position
 * Difficulty: Hard
 * Tags: array, tree, search, binary search, LIS
 * 
 * Approach: Longest Increasing Subsequence (LIS) with binary search
 * Time Complexity: O(n log n) where n is obstacles
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] longestObstacleCourseAtEachPosition(int[] obstacles) {
        int n = obstacles.length;
        int[] result = new int[n];
        List<Integer> dp = new ArrayList<>();  // dp[i] = smallest ending value for LIS of length i+1
        
        for (int i = 0; i < n; i++) {
            int idx = binarySearchRight(dp, obstacles[i]);
            if (idx == dp.size()) {
                dp.add(obstacles[i]);
            } else {
                dp.set(idx, obstacles[i]);
            }
            result[i] = idx + 1;
        }
        
        return result;
    }
    
    private int binarySearchRight(List<Integer> list, int target) {
        int left = 0, right = list.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (list.get(mid) <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
}