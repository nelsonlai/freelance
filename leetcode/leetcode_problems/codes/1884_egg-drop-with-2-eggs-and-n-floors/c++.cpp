/*
 * Problem: Egg Drop With 2 Eggs and N Floors
 * Difficulty: Medium
 * Tags: dp, math
 * 
 * Approach: DP - dp[moves][eggs] = max floors we can test
 * Time Complexity: O(n) where n is floors
 * Space Complexity: O(1)
 */

class Solution {
public:
    int twoEggDrop(int n) {
        int moves = 0;
        int floors = 0;
        
        while (floors < n) {
            moves++;
            floors += moves;
        }
        
        return moves;
    }
};