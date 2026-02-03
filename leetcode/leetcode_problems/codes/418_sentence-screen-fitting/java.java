/**
 * Problem: Sentence Screen Fitting
 * Difficulty: Medium
 * Tags: array, string, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class Solution {
    public int wordsTyping(String[] sentence, int rows, int cols) {
        String s = String.join(" ", sentence) + " ";
        int start = 0;
        int n = s.length();
        
        for (int i = 0; i < rows; i++) {
            start += cols;
            if (s.charAt(start % n) == ' ') {
                start++;
            } else {
                while (start > 0 && s.charAt((start - 1) % n) != ' ') {
                    start--;
                }
            }
        }
        
        return start / n;
    }
}