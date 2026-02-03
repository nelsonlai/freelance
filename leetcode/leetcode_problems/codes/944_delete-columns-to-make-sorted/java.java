/**
 * Problem: Delete Columns to Make Sorted
 * Difficulty: Easy
 * Tags: array, string, graph, sort
 * 
 * Approach: Check each column to see if it's sorted
 * Time Complexity: O(n * m) where n is number of strings, m is length
 * Space Complexity: O(1)
 */

class Solution {
    public int minDeletionSize(String[] strs) {
        int count = 0;
        int n = strs.length;
        int m = strs[0].length();
        
        for (int j = 0; j < m; j++) {
            for (int i = 1; i < n; i++) {
                if (strs[i].charAt(j) < strs[i-1].charAt(j)) {
                    count++;
                    break;
                }
            }
        }
        
        return count;
    }
}