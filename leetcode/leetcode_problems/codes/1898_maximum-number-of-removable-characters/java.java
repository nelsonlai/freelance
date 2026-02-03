/**
 * Problem: Maximum Number of Removable Characters
 * Difficulty: Medium
 * Tags: array, string, search, binary search
 * 
 * Approach: Binary search on number of removals, check if p is still subsequence
 * Time Complexity: O(k log k) where k is removable length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int maximumRemovals(String s, String p, int[] removable) {
        int left = 0, right = removable.length;
        int result = 0;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canRemove(s, p, removable, mid)) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    private boolean canRemove(String s, String p, int[] removable, int k) {
        Set<Integer> removed = new HashSet<>();
        for (int i = 0; i < k; i++) {
            removed.add(removable[i]);
        }
        
        int j = 0;
        for (int i = 0; i < s.length() && j < p.length(); i++) {
            if (removed.contains(i)) {
                continue;
            }
            if (s.charAt(i) == p.charAt(j)) {
                j++;
            }
        }
        
        return j == p.length();
    }
}