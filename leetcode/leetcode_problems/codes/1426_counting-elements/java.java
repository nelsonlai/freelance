/**
 * Problem: Counting Elements
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int countElements(int[] arr) {
        Set<Integer> set = new HashSet<>();
        for (int num : arr) {
            set.add(num);
        }
        
        int count = 0;
        for (int num : arr) {
            if (set.contains(num + 1)) {
                count++;
            }
        }
        
        return count;
    }
}