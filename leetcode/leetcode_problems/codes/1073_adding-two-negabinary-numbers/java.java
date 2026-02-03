/**
 * Problem: Adding Two Negabinary Numbers
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Add digit by digit, handle carries in base -2
 * Time Complexity: O(max(len(arr1), len(arr2)))
 * Space Complexity: O(max(len(arr1), len(arr2)))
 */

import java.util.*;

class Solution {
    public int[] addNegabinary(int[] arr1, int[] arr2) {
        List<Integer> result = new ArrayList<>();
        int carry = 0;
        int i = arr1.length - 1, j = arr2.length - 1;
        
        while (i >= 0 || j >= 0 || carry != 0) {
            int total = carry;
            if (i >= 0) {
                total += arr1[i--];
            }
            if (j >= 0) {
                total += arr2[j--];
            }
            
            result.add(total & 1);
            carry = -(total >> 1);
        }
        
        while (result.size() > 1 && result.get(result.size() - 1) == 0) {
            result.remove(result.size() - 1);
        }
        
        Collections.reverse(result);
        return result.stream().mapToInt(x -> x).toArray();
    }
}