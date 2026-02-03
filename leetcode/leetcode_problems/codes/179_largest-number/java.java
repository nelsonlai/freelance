/**
 * Problem: Largest Number
 * Difficulty: Medium
 * Tags: array, string, greedy, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String largestNumber(int[] nums) {
        String[] numStrings = new String[nums.length];
        for (int i = 0; i < nums.length; i++) {
            numStrings[i] = String.valueOf(nums[i]);
        }
        
        Arrays.sort(numStrings, (a, b) -> {
            String order1 = a + b;
            String order2 = b + a;
            return order2.compareTo(order1);
        });
        
        if (numStrings[0].equals("0")) {
            return "0";
        }
        
        StringBuilder result = new StringBuilder();
        for (String num : numStrings) {
            result.append(num);
        }
        
        return result.toString();
    }
}