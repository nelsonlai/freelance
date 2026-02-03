/**
 * Problem: Minimum Number of Operations to Make Array Continuous
 * Difficulty: Hard
 * Tags: array, hash, search, sliding window
 * 
 * Approach: Sort and deduplicate, use sliding window to find longest valid subarray
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;
        Set<Integer> uniqueSet = new TreeSet<>();
        for (int num : nums) {
            uniqueSet.add(num);
        }
        
        List<Integer> unique = new ArrayList<>(uniqueSet);
        int m = unique.size();
        
        // Find longest subarray where unique[j] - unique[i] < n
        int maxKeep = 0;
        int j = 0;
        
        for (int i = 0; i < m; i++) {
            while (j < m && unique.get(j) < unique.get(i) + n) {
                j++;
            }
            maxKeep = Math.max(maxKeep, j - i);
        }
        
        return n - maxKeep;
    }
}