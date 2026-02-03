/**
 * Problem: Check If a String Contains All Binary Codes of Size K
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Extract all substrings of length k, check if we have 2^k unique codes
 * Time Complexity: O(n * k) where n is length of s
 * Space Complexity: O(2^k) for set
 */

import java.util.*;

class Solution {
    public boolean hasAllCodes(String s, int k) {
        Set<String> seen = new HashSet<>();
        for (int i = 0; i <= s.length() - k; i++) {
            seen.add(s.substring(i, i + k));
        }
        return seen.size() == (1 << k);
    }
}