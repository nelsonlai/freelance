/**
 * Problem: Kth Missing Positive Number
 * Difficulty: Easy
 * Tags: array, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int findKthPositive(int[] arr, int k) {
        int left = 0, right = arr.length;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            int missing = arr[mid] - mid - 1;
            if (missing < k) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return left + k;
    }
}