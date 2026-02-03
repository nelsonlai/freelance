/**
 * Problem: Sort Transformed Array
 * Difficulty: Medium
 * Tags: array, math, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int[] sortTransformedArray(int[] nums, int a, int b, int c) {
        int[] transformed = new int[nums.length];
        for (int i = 0; i < nums.length; i++) {
            transformed[i] = a * nums[i] * nums[i] + b * nums[i] + c;
        }
        
        if (a == 0) {
            return b >= 0 ? transformed : reverse(transformed);
        }
        
        double vertex = -b / (2.0 * a);
        int[] result = new int[nums.length];
        int left = 0, right = nums.length - 1;
        int idx = 0;
        
        while (left <= right) {
            if (Math.abs(nums[left] - vertex) > Math.abs(nums[right] - vertex)) {
                result[idx++] = transformed[left++];
            } else {
                result[idx++] = transformed[right--];
            }
        }
        
        return a < 0 ? result : reverse(result);
    }
    
    private int[] reverse(int[] arr) {
        int left = 0, right = arr.length - 1;
        while (left < right) {
            int temp = arr[left];
            arr[left] = arr[right];
            arr[right] = temp;
            left++;
            right--;
        }
        return arr;
    }
}