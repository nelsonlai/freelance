/**
 * Problem: Bulls and Cows
 * Difficulty: Medium
 * Tags: string, hash
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public String getHint(String secret, String guess) {
        int bulls = 0;
        int cows = 0;
        
        Map<Character, Integer> secretCount = new HashMap<>();
        Map<Character, Integer> guessCount = new HashMap<>();
        
        for (int i = 0; i < secret.length(); i++) {
            if (secret.charAt(i) == guess.charAt(i)) {
                bulls++;
            } else {
                secretCount.put(secret.charAt(i), secretCount.getOrDefault(secret.charAt(i), 0) + 1);
                guessCount.put(guess.charAt(i), guessCount.getOrDefault(guess.charAt(i), 0) + 1);
            }
        }
        
        for (char c : secretCount.keySet()) {
            if (guessCount.containsKey(c)) {
                cows += Math.min(secretCount.get(c), guessCount.get(c));
            }
        }
        
        return bulls + "A" + cows + "B";
    }
}