/**
 * Problem: Minimum Domino Rotations For Equal Row
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Try making all tops or all bottoms equal to first top or first bottom value
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public int minDominoRotations(int[] tops, int[] bottoms) {
        int result = check(tops, bottoms, tops[0]);
        if (result != -1) return result;
        return check(tops, bottoms, bottoms[0]);
    }
    
    private int check(int[] tops, int[] bottoms, int target) {
        int topRotations = 0, bottomRotations = 0;
        for (int i = 0; i < tops.length; i++) {
            if (tops[i] != target && bottoms[i] != target) {
                return -1;
            }
            if (tops[i] != target) topRotations++;
            if (bottoms[i] != target) bottomRotations++;
        }
        return Math.min(topRotations, bottomRotations);
    }
}