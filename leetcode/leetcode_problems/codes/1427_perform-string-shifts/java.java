/**
 * Problem: Perform String Shifts
 * Difficulty: Easy
 * Tags: array, string, math
 * 
 * Approach: Calculate net shift amount, rotate string
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(n) for result
 */

class Solution {
    public String stringShift(String s, int[][] shift) {
        int totalShift = 0;
        for (int[] sh : shift) {
            if (sh[0] == 0) {
                totalShift -= sh[1];
            } else {
                totalShift += sh[1];
            }
        }
        
        totalShift %= s.length();
        if (totalShift < 0) {
            totalShift += s.length();
        }
        
        return s.substring(s.length() - totalShift) + s.substring(0, s.length() - totalShift);
    }
}