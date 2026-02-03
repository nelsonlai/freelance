/**
 * Problem: Smallest Integer Divisible by K
 * Difficulty: Medium
 * Tags: math, hash
 * 
 * Approach: Track remainders - if remainder repeats, no solution exists
 * Time Complexity: O(k)
 * Space Complexity: O(k) for remainder set
 */

import java.util.*;

class Solution {
    public int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) {
            return -1;
        }
        
        int remainder = 0;
        Set<Integer> seen = new HashSet<>();
        
        for (int length = 1; length <= k; length++) {
            remainder = (remainder * 10 + 1) % k;
            if (remainder == 0) {
                return length;
            }
            if (seen.contains(remainder)) {
                return -1;
            }
            seen.add(remainder);
        }
        
        return -1;
    }
}