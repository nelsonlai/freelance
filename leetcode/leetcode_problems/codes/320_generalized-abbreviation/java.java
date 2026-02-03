/**
 * Problem: Generalized Abbreviation
 * Difficulty: Medium
 * Tags: string, tree
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public List<String> generateAbbreviations(String word) {
        List<String> result = new ArrayList<>();
        backtrack(word, 0, "", 0, result);
        return result;
    }
    
    private void backtrack(String word, int index, String current, int count, List<String> result) {
        if (index == word.length()) {
            if (count > 0) {
                current += count;
            }
            result.add(current);
            return;
        }
        
        backtrack(word, index + 1, current, count + 1, result);
        
        if (count > 0) {
            backtrack(word, index + 1, current + count + word.charAt(index), 0, result);
        } else {
            backtrack(word, index + 1, current + word.charAt(index), 0, result);
        }
    }
}