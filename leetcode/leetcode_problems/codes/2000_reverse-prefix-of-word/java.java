/**
 * Problem: Reverse Prefix of Word
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Find first occurrence of ch, reverse prefix up to that index
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

class Solution {
    public String reversePrefix(String word, char ch) {
        int idx = word.indexOf(ch);
        if (idx == -1) {
            return word;
        }
        
        StringBuilder sb = new StringBuilder(word.substring(0, idx + 1));
        return sb.reverse().toString() + word.substring(idx + 1);
    }
}