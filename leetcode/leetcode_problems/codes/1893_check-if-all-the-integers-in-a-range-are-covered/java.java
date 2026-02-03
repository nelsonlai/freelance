/**
 * Problem: Check if All the Integers in a Range Are Covered
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Mark all covered numbers, check if range is fully covered
 * Time Complexity: O(n * range_size) where n is ranges
 * Space Complexity: O(range_size)
 */

import java.util.*;

class Solution {
    public boolean isCovered(int[][] ranges, int left, int right) {
        Set<Integer> covered = new HashSet<>();
        for (int[] range : ranges) {
            for (int i = range[0]; i <= range[1]; i++) {
                covered.add(i);
            }
        }
        
        for (int i = left; i <= right; i++) {
            if (!covered.contains(i)) {
                return false;
            }
        }
        
        return true;
    }
}