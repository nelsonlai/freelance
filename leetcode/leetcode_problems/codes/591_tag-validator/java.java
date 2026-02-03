/**
 * Problem: Tag Validator
 * Difficulty: Hard
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public boolean isValid(String code) {
        if (!code.startsWith("<") || !code.endsWith(">")) {
            return false;
        }
        
        Stack<String> stack = new Stack<>();
        int i = 0;
        
        while (i < code.length()) {
            if (i > 0 && stack.isEmpty()) {
                return false;
            }
            
            if (code.startsWith("<![CDATA[", i)) {
                int j = i + 9;
                i = code.indexOf("]]>", j);
                if (i == -1) {
                    return false;
                }
                i += 3;
            } else if (code.startsWith("</", i)) {
                int j = i + 2;
                i = code.indexOf(">", j);
                if (i == -1) {
                    return false;
                }
                String tag = code.substring(j, i);
                if (stack.isEmpty() || !stack.pop().equals(tag)) {
                    return false;
                }
                i++;
            } else if (code.startsWith("<", i)) {
                int j = i + 1;
                i = code.indexOf(">", j);
                if (i == -1) {
                    return false;
                }
                String tag = code.substring(j, i);
                if (tag.isEmpty() || tag.length() > 9 || !tag.matches("[A-Z]+")) {
                    return false;
                }
                stack.push(tag);
                i++;
            } else {
                i++;
            }
        }
        
        return stack.isEmpty();
    }
}