/**
 * Problem: Find Greatest Common Divisor of Array
 * Difficulty: Easy
 * Tags: array, math
 * 
 * Approach: Find GCD of min and max elements
 * Time Complexity: O(n + log(min, max)) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int findGCD(int[] nums) {
        int min = Integer.MAX_VALUE;
        int max = Integer.MIN_VALUE;
        
        for (int num : nums) {
            min = Math.min(min, num);
            max = Math.max(max, num);
        }
        
        return gcd(min, max);
    }
    
    private int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
}