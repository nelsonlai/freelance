/**
 * Problem: Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.Arrays;

class Solution {
    public int maxArea(int h, int w, int[] horizontalCuts, int[] verticalCuts) {
        int MOD = 1000000007;
        Arrays.sort(horizontalCuts);
        Arrays.sort(verticalCuts);
        
        int maxH = Math.max(horizontalCuts[0], h - horizontalCuts[horizontalCuts.length - 1]);
        for (int i = 1; i < horizontalCuts.length; i++) {
            maxH = Math.max(maxH, horizontalCuts[i] - horizontalCuts[i - 1]);
        }
        
        int maxW = Math.max(verticalCuts[0], w - verticalCuts[verticalCuts.length - 1]);
        for (int i = 1; i < verticalCuts.length; i++) {
            maxW = Math.max(maxW, verticalCuts[i] - verticalCuts[i - 1]);
        }
        
        return (int)((long)maxH * maxW % MOD);
    }
}