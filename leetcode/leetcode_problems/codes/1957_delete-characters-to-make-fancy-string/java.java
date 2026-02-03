/**
 * Problem: Delete Characters to Make Fancy String
 * Difficulty: Easy
 * Tags: string, greedy
 * 
 * Approach: Remove characters that appear 3+ times consecutively
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public String makeFancyString(String s) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            int len = result.length();
            if (len >= 2 && result.charAt(len - 1) == c && result.charAt(len - 2) == c) {
                continue;
            }
            result.append(c);
        }
        return result.toString();
    }
}