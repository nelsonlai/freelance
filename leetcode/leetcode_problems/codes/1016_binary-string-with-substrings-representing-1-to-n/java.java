/**
 * Problem: Binary String With Substrings Representing 1 To N
 * Difficulty: Medium
 * Tags: array, string, tree, hash
 * 
 * Approach: Check if all numbers from 1 to n have binary representation as substring
 * Time Complexity: O(n * log n * m) where m is string length
 * Space Complexity: O(n) for set
 */

import java.util.*;

class Solution {
    public boolean queryString(String s, int n) {
        Set<Integer> found = new HashSet<>();
        
        for (int i = 0; i < s.length(); i++) {
            int num = 0;
            for (int j = i; j < Math.min(i + 32, s.length()); j++) {
                num = num * 2 + (s.charAt(j) - '0');
                if (num >= 1 && num <= n) {
                    found.add(num);
                }
                if (num > n) {
                    break;
                }
            }
        }
        
        return found.size() == n;
    }
}