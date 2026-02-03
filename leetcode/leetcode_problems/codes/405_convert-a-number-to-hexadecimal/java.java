/**
 * Problem: Convert a Number to Hexadecimal
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String toHex(int num) {
        if (num == 0) {
            return "0";
        }
        
        char[] hexChars = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        StringBuilder result = new StringBuilder();
        
        long n = num;
        if (n < 0) {
            n = (1L << 32) + n;
        }
        
        while (n > 0) {
            result.append(hexChars[(int)(n % 16)]);
            n /= 16;
        }
        
        return result.reverse().toString();
    }
}