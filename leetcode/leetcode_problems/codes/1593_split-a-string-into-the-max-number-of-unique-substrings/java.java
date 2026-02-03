/**
 * Problem: Split a String Into the Max Number of Unique Substrings
 * Difficulty: Medium
 * Tags: string, tree, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public int maxUniqueSplit(String s) {
        return backtrack(s, 0, new HashSet<>());
    }
    
    private int backtrack(String s, int start, Set<String> seen) {
        if (start == s.length()) {
            return 0;
        }
        
        int result = 0;
        for (int end = start + 1; end <= s.length(); end++) {
            String substring = s.substring(start, end);
            if (!seen.contains(substring)) {
                seen.add(substring);
                result = Math.max(result, 1 + backtrack(s, end, seen));
                seen.remove(substring);
            }
        }
        
        return result;
    }
}