/**
 * Problem: Remove All Occurrences of a Substring
 * Difficulty: Medium
 * Tags: string, stack
 * 
 * Approach: Use stack to simulate removal, keep removing until no more occurrences
 * Time Complexity: O(n * m) where n is s length, m is part length
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public String removeOccurrences(String s, String part) {
        StringBuilder sb = new StringBuilder();
        int partLen = part.length();
        
        for (char c : s.toCharArray()) {
            sb.append(c);
            if (sb.length() >= partLen) {
                String last = sb.substring(sb.length() - partLen);
                if (last.equals(part)) {
                    sb.setLength(sb.length() - partLen);
                }
            }
        }
        
        return sb.toString();
    }
}