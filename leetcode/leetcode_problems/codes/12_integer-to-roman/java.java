/**
 * Problem: Integer to Roman
 * Difficulty: Medium
 * Tags: string, math, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

class Solution {
    public String intToRoman(int num) {
        int[] values = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        String[] symbols = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
        
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < values.length; i++) {
            int count = num / values[i];
            for (int j = 0; j < count; j++) {
                result.append(symbols[i]);
            }
            num %= values[i];
        }
        
        return result.toString();
    }
}