/**
 * Problem: Maximum Value after Insertion
 * Difficulty: Medium
 * Tags: string, greedy
 * 
 * Approach: Insert x at first position where it increases value
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public String maxValue(String n, int x) {
        boolean isNegative = n.charAt(0) == '-';
        
        if (isNegative) {
            for (int i = 1; i < n.length(); i++) {
                if (Character.getNumericValue(n.charAt(i)) > x) {
                    return n.substring(0, i) + x + n.substring(i);
                }
            }
            return n + x;
        } else {
            for (int i = 0; i < n.length(); i++) {
                if (Character.getNumericValue(n.charAt(i)) < x) {
                    return n.substring(0, i) + x + n.substring(i);
                }
            }
            return n + x;
        }
    }
}