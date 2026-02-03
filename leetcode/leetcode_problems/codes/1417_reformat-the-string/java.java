/**
 * Problem: Reformat The String
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: Separate digits and letters, interleave starting with larger group
 * Time Complexity: O(n) where n is length of s
 * Space Complexity: O(n) for result
 */

import java.util.*;

class Solution {
    public String reformat(String s) {
        List<Character> digits = new ArrayList<>();
        List<Character> letters = new ArrayList<>();
        
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                digits.add(c);
            } else {
                letters.add(c);
            }
        }
        
        if (Math.abs(digits.size() - letters.size()) > 1) {
            return "";
        }
        
        StringBuilder result = new StringBuilder();
        if (digits.size() >= letters.size()) {
            for (int i = 0; i < letters.size(); i++) {
                result.append(digits.get(i));
                result.append(letters.get(i));
            }
            if (digits.size() > letters.size()) {
                result.append(digits.get(digits.size() - 1));
            }
        } else {
            for (int i = 0; i < digits.size(); i++) {
                result.append(letters.get(i));
                result.append(digits.get(i));
            }
            result.append(letters.get(letters.size() - 1));
        }
        
        return result.toString();
    }
}