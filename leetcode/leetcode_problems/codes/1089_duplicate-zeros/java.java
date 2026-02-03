/**
 * Problem: Duplicate Zeros
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Two passes - count zeros, then fill from right to left
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
    public void duplicateZeros(int[] arr) {
        int zeros = 0;
        for (int num : arr) {
            if (num == 0) zeros++;
        }
        
        int n = arr.length;
        for (int i = n - 1; i >= 0; i--) {
            if (i + zeros < n) {
                arr[i + zeros] = arr[i];
            }
            if (arr[i] == 0) {
                zeros--;
                if (i + zeros < n) {
                    arr[i + zeros] = 0;
                }
            }
        }
    }
}