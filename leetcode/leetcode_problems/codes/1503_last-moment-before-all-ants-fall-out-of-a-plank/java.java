/**
 * Problem: Last Moment Before All Ants Fall Out of a Plank
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Ants passing each other is equivalent to passing through. Max time is max distance from left or (n - min distance from right)
 * Time Complexity: O(n) where n is length of arrays
 * Space Complexity: O(1)
 */

class Solution {
    public int getLastMoment(int n, int[] left, int[] right) {
        int maxLeft = 0;
        for (int pos : left) {
            maxLeft = Math.max(maxLeft, pos);
        }
        
        int minRight = n;
        for (int pos : right) {
            minRight = Math.min(minRight, pos);
        }
        
        return Math.max(maxLeft, n - minRight);
    }
}