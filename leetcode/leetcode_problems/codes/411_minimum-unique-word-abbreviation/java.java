/**
 * Problem: Minimum Unique Word Abbreviation
 * Difficulty: Hard
 * Tags: array, string, tree
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

import java.util.*;

class Solution {
    public String minAbbreviation(String target, String[] dictionary) {
        int n = target.length();
        List<String> dict = new ArrayList<>();
        for (String word : dictionary) {
            if (word.length() == n) {
                dict.add(word);
            }
        }
        
        int minLen = Integer.MAX_VALUE;
        String result = target;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            String abbr = getAbbr(target, mask);
            if (abbr.length() < minLen && isValid(target, mask, dict)) {
                minLen = abbr.length();
                result = abbr;
            }
        }
        
        return result;
    }
    
    private String getAbbr(String word, int mask) {
        StringBuilder sb = new StringBuilder();
        int count = 0;
        for (int i = 0; i < word.length(); i++) {
            if ((mask & (1 << i)) != 0) {
                if (count > 0) {
                    sb.append(count);
                    count = 0;
                }
                sb.append(word.charAt(i));
            } else {
                count++;
            }
        }
        if (count > 0) {
            sb.append(count);
        }
        return sb.toString();
    }
    
    private boolean isValid(String target, int mask, List<String> dictionary) {
        for (String word : dictionary) {
            boolean valid = true;
            for (int i = 0; i < target.length(); i++) {
                if ((mask & (1 << i)) != 0) {
                    if (target.charAt(i) != word.charAt(i)) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid) {
                return false;
            }
        }
        return true;
    }
}