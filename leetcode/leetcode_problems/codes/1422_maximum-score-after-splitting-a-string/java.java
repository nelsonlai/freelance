/**
 * Problem: Maximum Score After Splitting a String
 * Difficulty: Easy
 * Tags: array, string, tree
 * 
 * Approach: Try all split positions, count zeros on left and ones on right
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

class Solution {
    public int maxScore(String s) {
        int maxScore = 0;
        for (int i = 1; i < s.length(); i++) {
            int leftZeros = 0;
            for (int j = 0; j < i; j++) {
                if (s.charAt(j) == '0') {
                    leftZeros++;
                }
            }
            int rightOnes = 0;
            for (int j = i; j < s.length(); j++) {
                if (s.charAt(j) == '1') {
                    rightOnes++;
                }
            }
            maxScore = Math.max(maxScore, leftZeros + rightOnes);
        }
        return maxScore;
    }
}