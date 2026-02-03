/**
 * Problem: Beautiful Arrangement II
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] constructArray(int n, int k) {
        int[] result = new int[n];
        int left = 1, right = n;
        int index = 0;
        
        while (left <= right) {
            if (k > 1) {
                if (k % 2 == 1) {
                    result[index++] = left++;
                } else {
                    result[index++] = right--;
                }
                k--;
            } else {
                result[index++] = left++;
            }
        }
        
        return result;
    }
}