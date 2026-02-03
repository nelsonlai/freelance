/**
 * Problem: Check if Word Equals Summation of Two Words
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Convert words to numbers, check if sum equals target
 * Time Complexity: O(n) where n is max word length
 * Space Complexity: O(1)
 */

class Solution {
    public boolean isSumEqual(String firstWord, String secondWord, String targetWord) {
        return wordToNum(firstWord) + wordToNum(secondWord) == wordToNum(targetWord);
    }
    
    private int wordToNum(String word) {
        StringBuilder sb = new StringBuilder();
        for (char c : word.toCharArray()) {
            sb.append(c - 'a');
        }
        return Integer.parseInt(sb.toString());
    }
}