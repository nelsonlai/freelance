/**
 * Problem: Check If String Is a Prefix of Array
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Concatenate words and check if equals s
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(n * m)
 */

class Solution {
    public boolean isPrefixString(String s, String[] words) {
        StringBuilder concatenated = new StringBuilder();
        for (String word : words) {
            concatenated.append(word);
            if (concatenated.toString().equals(s)) {
                return true;
            }
            if (concatenated.length() >= s.length()) {
                return false;
            }
        }
        return false;
    }
}