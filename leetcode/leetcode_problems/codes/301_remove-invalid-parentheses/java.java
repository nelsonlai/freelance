/**
 * Problem: Remove Invalid Parentheses
 * Difficulty: Hard
 * Tags: string, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> removeInvalidParentheses(String s) {
        List<String> result = new ArrayList<>();
        remove(s, 0, 0, new char[]{'(', ')'}, result);
        return result;
    }
    
    private void remove(String s, int lastI, int lastJ, char[] pair, List<String> result) {
        int count = 0;
        for (int i = lastI; i < s.length(); i++) {
            if (s.charAt(i) == pair[0]) count++;
            if (s.charAt(i) == pair[1]) count--;
            if (count >= 0) continue;
            
            for (int j = lastJ; j <= i; j++) {
                if (s.charAt(j) == pair[1] && (j == lastJ || s.charAt(j - 1) != pair[1])) {
                    remove(s.substring(0, j) + s.substring(j + 1), i, j, pair, result);
                }
            }
            return;
        }
        
        String reversed = new StringBuilder(s).reverse().toString();
        if (pair[0] == '(') {
            remove(reversed, 0, 0, new char[]{')', '('}, result);
        } else {
            result.add(reversed);
        }
    }
}