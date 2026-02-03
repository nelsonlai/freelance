/**
 * Problem: Base 7
 * Difficulty: Easy
 * Tags: string, math
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String convertToBase7(int num) {
        if (num == 0) {
            return "0";
        }
        
        boolean negative = num < 0;
        num = Math.abs(num);
        StringBuilder result = new StringBuilder();
        
        while (num > 0) {
            result.append(num % 7);
            num /= 7;
        }
        
        if (negative) {
            result.append("-");
        }
        
        return result.reverse().toString();
    }
}