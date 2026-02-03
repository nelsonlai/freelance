/**
 * Problem: Self Crossing
 * Difficulty: Hard
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public boolean isSelfCrossing(int[] distance) {
        if (distance.length < 4) {
            return false;
        }
        
        for (int i = 3; i < distance.length; i++) {
            if (distance[i] >= distance[i - 2] && distance[i - 1] <= distance[i - 3]) {
                return true;
            }
            if (i >= 4 && distance[i - 1] == distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2]) {
                return true;
            }
            if (i >= 5 && distance[i - 2] >= distance[i - 4] && 
                distance[i - 1] <= distance[i - 3] && 
                distance[i] + distance[i - 4] >= distance[i - 2] && 
                distance[i - 1] + distance[i - 5] >= distance[i - 3]) {
                return true;
            }
        }
        
        return false;
    }
}