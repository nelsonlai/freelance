/**
 * Problem: Can Make Arithmetic Progression From Sequence
 * Difficulty: Easy
 * Tags: array, sort
 * 
 * Approach: Sort array, check if differences between consecutive elements are equal
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.Arrays;

class Solution {
    public boolean canMakeArithmeticProgression(int[] arr) {
        Arrays.sort(arr);
        int diff = arr[1] - arr[0];
        for (int i = 2; i < arr.length; i++) {
            if (arr[i] - arr[i-1] != diff) {
                return false;
            }
        }
        return true;
    }
}