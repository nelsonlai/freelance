/**
 * Problem: Check if All Characters Have Equal Number of Occurrences
 * Difficulty: Easy
 * Tags: string, hash
 * 
 * Approach: Count occurrences, check if all equal
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1) - fixed 26 characters
 */

import java.util.*;

class Solution {
    public boolean areOccurrencesEqual(String s) {
        int[] count = new int[26];
        for (char c : s.toCharArray()) {
            count[c - 'a']++;
        }
        
        int first = -1;
        for (int c : count) {
            if (c > 0) {
                if (first == -1) {
                    first = c;
                } else if (c != first) {
                    return false;
                }
            }
        }
        
        return true;
    }
}