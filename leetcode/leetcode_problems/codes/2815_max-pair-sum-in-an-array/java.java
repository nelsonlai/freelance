/**
 * Problem: Max Pair Sum in an Array
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int maxSum(int[] nums) {
        Map<Integer, Integer> maxDigitToNum = new HashMap<>();
        int result = -1;
        
        for (int num : nums) {
            int maxDigit = maxDigit(num);
            if (maxDigitToNum.containsKey(maxDigit)) {
                result = Math.max(result, maxDigitToNum.get(maxDigit) + num);
                maxDigitToNum.put(maxDigit, Math.max(maxDigitToNum.get(maxDigit), num));
            } else {
                maxDigitToNum.put(maxDigit, num);
            }
        }
        
        return result;
    }
    
    private int maxDigit(int num) {
        int max = 0;
        while (num > 0) {
            max = Math.max(max, num % 10);
            num /= 10;
        }
        return max;
    }
}