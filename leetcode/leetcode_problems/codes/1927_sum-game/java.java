/**
 * Problem: Sum Game
 * Difficulty: Medium
 * Tags: string, greedy, math
 * 
 * Approach: Alice wins if sum difference != 0 or question mark difference is odd
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean sumGame(String num) {
        int n = num.length();
        int leftSum = 0, leftQ = 0;
        int rightSum = 0, rightQ = 0;
        
        for (int i = 0; i < n / 2; i++) {
            if (num.charAt(i) == '?') {
                leftQ++;
            } else {
                leftSum += num.charAt(i) - '0';
            }
        }
        
        for (int i = n / 2; i < n; i++) {
            if (num.charAt(i) == '?') {
                rightQ++;
            } else {
                rightSum += num.charAt(i) - '0';
            }
        }
        
        int diff = leftSum - rightSum;
        int qDiff = leftQ - rightQ;
        
        if (qDiff == 0) {
            return diff != 0;
        }
        
        if (qDiff % 2 == 1) {
            return true;
        }
        
        return diff != 9 * qDiff / 2;
    }
}