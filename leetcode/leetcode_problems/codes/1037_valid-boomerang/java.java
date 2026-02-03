/**
 * Problem: Valid Boomerang
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Check if three points are collinear using cross product
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

class Solution {
    public boolean isBoomerang(int[][] points) {
        int[] p1 = points[0], p2 = points[1], p3 = points[2];
        // Check if they are collinear using cross product
        return (p2[1] - p1[1]) * (p3[0] - p2[0]) != (p3[1] - p2[1]) * (p2[0] - p1[0]);
    }
}