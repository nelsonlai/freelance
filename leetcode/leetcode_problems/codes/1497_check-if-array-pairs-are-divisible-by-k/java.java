/**
 * Problem: Check If Array Pairs Are Divisible by k
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean canArrange(int[] arr, int k) {
        Map<Integer, Integer> remainderCount = new HashMap<>();
        for (int num : arr) {
            int remainder = ((num % k) + k) % k;
            remainderCount.put(remainder, remainderCount.getOrDefault(remainder, 0) + 1);
        }
        
        for (Map.Entry<Integer, Integer> entry : remainderCount.entrySet()) {
            int remainder = entry.getKey();
            int count = entry.getValue();
            
            if (remainder == 0) {
                if (count % 2 != 0) {
                    return false;
                }
            } else if (remainder * 2 == k) {
                if (count % 2 != 0) {
                    return false;
                }
            } else {
                int complement = k - remainder;
                if (!remainderCount.getOrDefault(complement, 0).equals(count)) {
                    return false;
                }
            }
        }
        
        return true;
    }
}