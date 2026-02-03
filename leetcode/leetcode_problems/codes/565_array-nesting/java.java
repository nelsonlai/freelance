/**
 * Problem: Array Nesting
 * Difficulty: Medium
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int arrayNesting(int[] nums) {
        boolean[] visited = new boolean[nums.length];
        int maxLength = 0;
        
        for (int i = 0; i < nums.length; i++) {
            if (!visited[i]) {
                int count = 0;
                int j = i;
                while (!visited[j]) {
                    visited[j] = true;
                    j = nums[j];
                    count++;
                }
                maxLength = Math.max(maxLength, count);
            }
        }
        
        return maxLength;
    }
}