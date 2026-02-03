/**
 * Problem: Minimum Number of Flips to Make the Binary String Alternating
 * Difficulty: Medium
 * Tags: array, string, sliding window
 * 
 * Approach: Try both patterns, use sliding window for circular string
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int minFlips(String s) {
        int n = s.length();
        String s2 = s + s;
        
        int diff1 = 0, diff2 = 0;
        int result = Integer.MAX_VALUE;
        
        for (int i = 0; i < n * 2; i++) {
            char expected1 = (i % 2 == 0) ? '0' : '1';
            char expected2 = (i % 2 == 0) ? '1' : '0';
            
            if (s2.charAt(i) != expected1) diff1++;
            if (s2.charAt(i) != expected2) diff2++;
            
            if (i >= n - 1) {
                result = Math.min(result, Math.min(diff1, diff2));
                int removeIdx = i - n + 1;
                char expected1Remove = (removeIdx % 2 == 0) ? '0' : '1';
                char expected2Remove = (removeIdx % 2 == 0) ? '1' : '0';
                
                if (s2.charAt(removeIdx) != expected1Remove) diff1--;
                if (s2.charAt(removeIdx) != expected2Remove) diff2--;
            }
        }
        
        return result;
    }
}