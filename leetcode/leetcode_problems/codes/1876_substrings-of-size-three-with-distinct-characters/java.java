/**
 * Problem: Substrings of Size Three with Distinct Characters
 * Difficulty: Easy
 * Tags: array, string, hash, sliding window
 * 
 * Approach: Sliding window of size 3, check if all characters distinct
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int countGoodSubstrings(String s) {
        if (s.length() < 3) {
            return 0;
        }
        
        int count = 0;
        for (int i = 0; i <= s.length() - 3; i++) {
            char c1 = s.charAt(i);
            char c2 = s.charAt(i + 1);
            char c3 = s.charAt(i + 2);
            if (c1 != c2 && c2 != c3 && c1 != c3) {
                count++;
            }
        }
        
        return count;
    }
}