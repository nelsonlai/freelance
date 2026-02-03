/**
 * Problem: Consecutive Characters
 * Difficulty: Easy
 * Tags: string, tree
 * 
 * Approach: Track current consecutive length, update max
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(1)
 */

class Solution {
    public int maxPower(String s) {
        int maxPower = 1;
        int currentPower = 1;
        
        for (int i = 1; i < s.length(); i++) {
            if (s.charAt(i) == s.charAt(i - 1)) {
                currentPower++;
                maxPower = Math.max(maxPower, currentPower);
            } else {
                currentPower = 1;
            }
        }
        
        return maxPower;
    }
}