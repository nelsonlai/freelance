/**
 * Problem: Squirrel Simulation
 * Difficulty: Medium
 * Tags: array, tree, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
    public int minDistance(int height, int width, int[] tree, int[] squirrel, int[][] nuts) {
        int total = 0;
        int maxDiff = Integer.MIN_VALUE;
        
        for (int[] nut : nuts) {
            int distToTree = Math.abs(nut[0] - tree[0]) + Math.abs(nut[1] - tree[1]);
            int distToSquirrel = Math.abs(nut[0] - squirrel[0]) + Math.abs(nut[1] - squirrel[1]);
            total += distToTree * 2;
            maxDiff = Math.max(maxDiff, distToTree - distToSquirrel);
        }
        
        return total - maxDiff;
    }
}