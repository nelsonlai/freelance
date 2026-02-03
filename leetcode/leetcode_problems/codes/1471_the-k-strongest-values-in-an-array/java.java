/**
 * Problem: The k Strongest Values in an Array
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int[] getStrongest(int[] arr, int k) {
        Arrays.sort(arr);
        int median = arr[(arr.length - 1) / 2];
        
        Integer[] arrObj = new Integer[arr.length];
        for (int i = 0; i < arr.length; i++) {
            arrObj[i] = arr[i];
        }
        
        Arrays.sort(arrObj, (a, b) -> {
            int strengthA = Math.abs(a - median);
            int strengthB = Math.abs(b - median);
            if (strengthA != strengthB) {
                return Integer.compare(strengthB, strengthA);
            }
            return Integer.compare(b, a);
        });
        
        int[] result = new int[k];
        for (int i = 0; i < k; i++) {
            result[i] = arrObj[i];
        }
        return result;
    }
}