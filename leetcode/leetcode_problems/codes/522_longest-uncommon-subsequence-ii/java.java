/**
 * Problem: Longest Uncommon Subsequence II
 * Difficulty: Medium
 * Tags: array, string, hash, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findLUSlength(String[] strs) {
        Arrays.sort(strs, (a, b) -> Integer.compare(b.length(), a.length()));
        
        for (int i = 0; i < strs.length; i++) {
            boolean isUncommon = true;
            for (int j = 0; j < strs.length; j++) {
                if (i != j && isSubsequence(strs[i], strs[j])) {
                    isUncommon = false;
                    break;
                }
            }
            if (isUncommon) {
                return strs[i].length();
            }
        }
        
        return -1;
    }
    
    private boolean isSubsequence(String s, String t) {
        int i = 0;
        for (char c : t.toCharArray()) {
            if (i < s.length() && s.charAt(i) == c) {
                i++;
            }
        }
        return i == s.length();
    }
}