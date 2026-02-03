/**
 * Problem: Number of Strings That Appear as Substrings in Word
 * Difficulty: Easy
 * Tags: array, string
 * 
 * Approach: Check if each pattern is a substring of word
 * Time Complexity: O(n * m) where n is patterns, m is word length
 * Space Complexity: O(1)
 */

class Solution {
    public int numOfStrings(String[] patterns, String word) {
        int count = 0;
        for (String pattern : patterns) {
            if (word.contains(pattern)) {
                count++;
            }
        }
        return count;
    }
}