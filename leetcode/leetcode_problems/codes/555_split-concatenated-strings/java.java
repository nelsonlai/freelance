/**
 * Problem: Split Concatenated Strings
 * Difficulty: Medium
 * Tags: array, string, graph, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String splitLoopedString(String[] strs) {
        String[] optimized = new String[strs.length];
        for (int i = 0; i < strs.length; i++) {
            String reversed = new StringBuilder(strs[i]).reverse().toString();
            optimized[i] = strs[i].compareTo(reversed) > 0 ? strs[i] : reversed;
        }
        
        String result = String.join("", optimized);
        
        for (int i = 0; i < strs.length; i++) {
            String[] candidates = {strs[i], new StringBuilder(strs[i]).reverse().toString()};
            for (String start : candidates) {
                for (int j = 0; j < start.length(); j++) {
                    StringBuilder candidate = new StringBuilder();
                    candidate.append(start.substring(j));
                    for (int k = i + 1; k < strs.length; k++) {
                        candidate.append(optimized[k]);
                    }
                    for (int k = 0; k < i; k++) {
                        candidate.append(optimized[k]);
                    }
                    candidate.append(start.substring(0, j));
                    if (candidate.toString().compareTo(result) > 0) {
                        result = candidate.toString();
                    }
                }
            }
        }
        
        return result;
    }
}