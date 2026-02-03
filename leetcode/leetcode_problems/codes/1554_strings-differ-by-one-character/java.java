/**
 * Problem: Strings Differ by One Character
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public boolean differByOne(String[] dict) {
        int n = dict.length;
        if (n == 0) {
            return false;
        }
        
        int m = dict[0].length();
        
        for (int j = 0; j < m; j++) {
            Set<String> seen = new HashSet<>();
            for (int i = 0; i < n; i++) {
                String masked = dict[i].substring(0, j) + "*" + dict[i].substring(j + 1);
                if (seen.contains(masked)) {
                    return true;
                }
                seen.add(masked);
            }
        }
        
        return false;
    }
}