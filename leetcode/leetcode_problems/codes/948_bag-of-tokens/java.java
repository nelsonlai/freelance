/**
 * Problem: Bag of Tokens
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Greedy - face up smallest tokens, face down largest tokens when needed
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int bagOfTokensScore(int[] tokens, int power) {
        Arrays.sort(tokens);
        int left = 0, right = tokens.length - 1;
        int score = 0;
        int maxScore = 0;
        
        while (left <= right) {
            if (power >= tokens[left]) {
                power -= tokens[left];
                score++;
                left++;
                maxScore = Math.max(maxScore, score);
            } else if (score > 0) {
                power += tokens[right];
                score--;
                right--;
            } else {
                break;
            }
        }
        
        return maxScore;
    }
}