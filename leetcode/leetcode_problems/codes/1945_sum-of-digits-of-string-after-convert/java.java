/**
 * Problem: Sum of Digits of String After Convert
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Convert to numbers, sum digits k times
 * Time Complexity: O(n * k) where n is length
 * Space Complexity: O(1)
 */

class Solution {
    public int getLucky(String s, int k) {
        StringBuilder numStr = new StringBuilder();
        for (char c : s.toCharArray()) {
            numStr.append(c - 'a' + 1);
        }
        
        for (int i = 0; i < k; i++) {
            long sum = 0;
            for (char c : numStr.toString().toCharArray()) {
                sum += c - '0';
            }
            numStr = new StringBuilder(String.valueOf(sum));
        }
        
        return Integer.parseInt(numStr.toString());
    }
}