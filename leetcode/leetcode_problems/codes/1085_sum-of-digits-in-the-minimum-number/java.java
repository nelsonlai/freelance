/**
 * Problem: Sum of Digits in the Minimum Number
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Find minimum, sum its digits, return parity
 * Time Complexity: O(n + log(min(nums)))
 * Space Complexity: O(1)
 */

class Solution {
    public int sumOfDigits(int[] nums) {
        int minNum = Integer.MAX_VALUE;
        for (int num : nums) {
            minNum = Math.min(minNum, num);
        }
        
        int digitSum = 0;
        while (minNum > 0) {
            digitSum += minNum % 10;
            minNum /= 10;
        }
        
        return 1 - (digitSum % 2);
    }
}