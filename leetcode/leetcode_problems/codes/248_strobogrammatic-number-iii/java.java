/**
 * Problem: Strobogrammatic Number III
 * Difficulty: Hard
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int strobogrammaticInRange(String low, String high) {
        int count = 0;
        List<String> result = new ArrayList<>();
        for (int n = low.length(); n <= high.length(); n++) {
            result.addAll(findStrobogrammatic(n, n));
        }
        for (String num : result) {
            if ((num.length() == low.length() && num.compareTo(low) < 0) ||
                (num.length() == high.length() && num.compareTo(high) > 0)) {
                continue;
            }
            count++;
        }
        return count;
    }
    
    private List<String> findStrobogrammatic(int m, int n) {
        if (m == 0) {
            return new ArrayList<>(Arrays.asList(""));
        }
        if (m == 1) {
            return new ArrayList<>(Arrays.asList("0", "1", "8"));
        }
        
        List<String> prev = findStrobogrammatic(m - 2, n);
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