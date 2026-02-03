/**
 * Problem: String Matching in an Array
 * Difficulty: Easy
 * Tags: array, string, tree
 * 
 * Approach: Check if each word is substring of any other word
 * Time Complexity: O(n^2 * m) where n is words, m is average length
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public List<String> stringMatching(String[] words) {
        List<String> result = new ArrayList<>();
        for (int i = 0; i < words.length; i++) {
            for (int j = 0; j < words.length; j++) {
                if (i != j && words[j].contains(words[i])) {
                    result.add(words[i]);
                    break;
                }
            }
        }
        return result;
    }
}