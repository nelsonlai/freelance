/**
 * Problem: Decode String
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public String decodeString(String s) {
        Stack<String> stringStack = new Stack<>();
        Stack<Integer> numStack = new Stack<>();
        String currentString = "";
        int currentNum = 0;
        
        for (char c : s.toCharArray()) {
            if (Character.isDigit(c)) {
                currentNum = currentNum * 10 + (c - '0');
            } else if (c == '[') {
                stringStack.push(currentString);
                numStack.push(currentNum);
                currentString = "";
                currentNum = 0;
            } else if (c == ']') {
                String prevString = stringStack.pop();
                int num = numStack.pop();
                StringBuilder sb = new StringBuilder(prevString);
                for (int i = 0; i < num; i++) {
                    sb.append(currentString);
                }
                currentString = sb.toString();
            } else {
                currentString += c;
            }
        }
        
        return currentString;
    }
}