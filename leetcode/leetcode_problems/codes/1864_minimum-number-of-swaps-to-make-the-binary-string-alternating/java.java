/**
 * Problem: Minimum Number of Swaps to Make the Binary String Alternating
 * Difficulty: Medium
 * Tags: string, greedy
 * 
 * Approach: Try both patterns (0-start, 1-start), count mismatches
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int minSwaps(String s) {
        int count0 = 0, count1 = 0;
        for (char c : s.toCharArray()) {
            if (c == '0') count0++;
            else count1++;
        }
        
        if (Math.abs(count0 - count1) > 1) {
            return -1;
        }
        
        if (count0 == count1) {
            return Math.min(countMismatches(s, "01"), countMismatches(s, "10"));
        } else if (count0 > count1) {
            return countMismatches(s, "01");
        } else {
            return countMismatches(s, "10");
        }
    }
    
    private int countMismatches(String s, String pattern) {
        int mismatches = 0;
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) != pattern.charAt(i % 2)) {
                mismatches++;
            }
        }
        return mismatches / 2;
    }
}