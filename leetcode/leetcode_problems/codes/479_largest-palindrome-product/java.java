/**
 * Problem: Largest Palindrome Product
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        
        long maxNum = (long)Math.pow(10, n) - 1;
        long minNum = (long)Math.pow(10, n - 1);
        
        for (long i = maxNum; i >= minNum; i--) {
            String left = String.valueOf(i);
            String palindromeStr = left + new StringBuilder(left).reverse().toString();
            long palindrome = Long.parseLong(palindromeStr);
            
            for (long j = maxNum; j * j >= palindrome; j--) {
                if (palindrome % j == 0 && palindrome / j >= minNum && palindrome / j <= maxNum) {
                    return (int)(palindrome % 1337);
                }
            }
        }
        
        return 0;
    }
}