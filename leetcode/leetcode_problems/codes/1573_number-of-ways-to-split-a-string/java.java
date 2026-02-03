/**
 * Problem: Number of Ways to Split a String
 * Difficulty: Medium
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    private static final int MOD = 1000000007;
    
    public int numWays(String s) {
        int totalOnes = 0;
        for (char c : s.toCharArray()) {
            if (c == '1') {
                totalOnes++;
            }
        }
        
        if (totalOnes % 3 != 0) {
            return 0;
        }
        
        if (totalOnes == 0) {
            long n = s.length();
            return (int) (((n - 1) * (n - 2) / 2) % MOD);
        }
        
        int target = totalOnes / 3;
        int count = 0;
        int firstEnd = 0;
        int secondStart = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '1') {
                count++;
                if (count == target) {
                    firstEnd = i;
                }
                if (count == target + 1) {
                    secondStart = i;
                }
            }
        }
        
        count = 0;
        int secondEnd = 0;
        int thirdStart = 0;
        
        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '1') {
                count++;
                if (count == 2 * target) {
                    secondEnd = i;
                }
                if (count == 2 * target + 1) {
                    thirdStart = i;
                }
            }
        }
        
        return (int) (((long)(secondStart - firstEnd) * (thirdStart - secondEnd)) % MOD);
    }
}