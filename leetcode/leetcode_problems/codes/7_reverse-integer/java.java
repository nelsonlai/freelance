/**
 * Problem: Reverse Integer
 * Difficulty: Medium
 * Tags: math
 * 
 * Approach: Optimized algorithm based on problem constraints
 * Time Complexity: O(n) to O(n^2) depending on approach
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int reverse(int x) {
        int result = 0;
        
        while (x != 0) {
            int digit = x % 10;
            x /= 10;
            
            if (result > Integer.MAX_VALUE / 10 || 
                (result == Integer.MAX_VALUE / 10 && digit > 7)) {
                return 0;
            }
            if (result < Integer.MIN_VALUE / 10 || 
                (result == Integer.MIN_VALUE / 10 && digit < -8)) {
                return 0;
            }
            
            result = result * 10 + digit;
        }
        
        return result;
    }
}