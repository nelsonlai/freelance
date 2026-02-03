/**
 * Problem: Number of Good Ways to Split a String
 * Difficulty: Medium
 * Tags: string, dp, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int numSplits(String s) {
        int n = s.length();
        int[] leftDistinct = new int[n];
        int[] rightDistinct = new int[n];
        
        Set<Character> seen = new HashSet<>();
        for (int i = 0; i < n; i++) {
            seen.add(s.charAt(i));
            leftDistinct[i] = seen.size();
        }
        
        seen = new HashSet<>();
        for (int i = n - 1; i >= 0; i--) {
            seen.add(s.charAt(i));
            rightDistinct[i] = seen.size();
        }
        
        int count = 0;
        for (int i = 0; i < n - 1; i++) {
            if (leftDistinct[i] == rightDistinct[i + 1]) {
                count++;
            }
        }
        
        return count;
    }
}