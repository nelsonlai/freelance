/**
 * Problem: Strobogrammatic Number II
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> findStrobogrammatic(int n) {
        return helper(n, n);
    }
    
    private List<String> helper(int m, int n) {
        if (m == 0) {
            return new ArrayList<>(Arrays.asList(""));
        }
        if (m == 1) {
            return new ArrayList<>(Arrays.asList("0", "1", "8"));
        }
        
        List<String> prev = helper(m - 2, n);
        List<String> result = new ArrayList<>();
        for (String s : prev) {
            if (m != n) {
                result.add("0" + s + "0");
            }
            result.add("1" + s + "1");
            result.add("6" + s + "9");
            result.add("8" + s + "8");
            result.add("9" + s + "6");
        }
        return result;
    }
}