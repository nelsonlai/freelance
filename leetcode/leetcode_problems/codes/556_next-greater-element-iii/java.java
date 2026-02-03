/**
 * Problem: Next Greater Element III
 * Difficulty: Medium
 * Tags: array, string, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int nextGreaterElement(int n) {
        char[] digits = String.valueOf(n).toCharArray();
        
        int i = digits.length - 2;
        while (i >= 0 && digits[i] >= digits[i + 1]) {
            i--;
        }
        
        if (i < 0) {
            return -1;
        }
        
        int j = digits.length - 1;
        while (digits[j] <= digits[i]) {
            j--;
        }
        
        char temp = digits[i];
        digits[i] = digits[j];
        digits[j] = temp;
        
        reverse(digits, i + 1, digits.length - 1);
        
        long result = Long.parseLong(new String(digits));
        return result <= Integer.MAX_VALUE ? (int)result : -1;
    }
    
    private void reverse(char[] arr, int start, int end) {
        while (start < end) {
            char temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
        }
    }
}