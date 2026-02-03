/**
 * Problem: Palindrome Permutation
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean canPermutePalindrome(String s) {
        Map<Character, Integer> count = new HashMap<>();
        for (char c : s.toCharArray()) {
            count.put(c, count.getOrDefault(c, 0) + 1);
        }
        
        int oddCount = 0;
        for (int v : count.values()) {
            if (v % 2 == 1) {
                oddCount++;
            }
        }
        
        return oddCount <= 1;
    }
}