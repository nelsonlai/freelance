/**
 * Problem: Maximum Distance in Arrays
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int maxDistance(List<List<Integer>> arrays) {
        int minVal = arrays.get(0).get(0);
        int maxVal = arrays.get(0).get(arrays.get(0).size() - 1);
        int result = 0;
        
        for (int i = 1; i < arrays.size(); i++) {
            List<Integer> arr = arrays.get(i);
            result = Math.max(result, Math.max(Math.abs(arr.get(arr.size() - 1) - minVal),
                                              Math.abs(maxVal - arr.get(0))));
            minVal = Math.min(minVal, arr.get(0));
            maxVal = Math.max(maxVal, arr.get(arr.size() - 1));
        }
        
        return result;
    }
}