/**
 * Problem: Range Addition
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] getModifiedArray(int length, int[][] updates) {
        int[] result = new int[length];
        
        for (int[] update : updates) {
            int start = update[0];
            int end = update[1];
            int inc = update[2];
            result[start] += inc;
            if (end + 1 < length) {
                result[end + 1] -= inc;
            }
        }
        
        for (int i = 1; i < length; i++) {
            result[i] += result[i - 1];
        }
        
        return result;
    }
}