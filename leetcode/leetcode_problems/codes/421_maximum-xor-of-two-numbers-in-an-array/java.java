/**
 * Problem: Maximum XOR of Two Numbers in an Array
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findMaximumXOR(int[] nums) {
        int maxXor = 0;
        int mask = 0;
        
        for (int i = 31; i >= 0; i--) {
            mask |= (1 << i);
            Set<Integer> prefixes = new HashSet<>();
            for (int num : nums) {
                prefixes.add(num & mask);
            }
            
            int temp = maxXor | (1 << i);
            for (int prefix : prefixes) {
                if (prefixes.contains(temp ^ prefix)) {
                    maxXor = temp;
                    break;
                }
            }
        }
        
        return maxXor;
    }
}