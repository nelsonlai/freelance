/**
 * Problem: Fixed Point
 * Difficulty: Easy
 * Tags: array, sort, search
 * 
 * Approach: Binary search - find smallest index where arr[i] == i
 * Time Complexity: O(log n)
 * Space Complexity: O(1)
 */

class Solution {
    public int fixedPoint(int[] arr) {
        int left = 0, right = arr.length - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] == mid) {
                result = mid;
                right = mid - 1;
            } else if (arr[mid] < mid) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
}