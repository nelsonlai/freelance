/**
 * Problem: Restore IP Addresses
 * Difficulty: Medium
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public List<String> restoreIpAddresses(String s) {
        List<String> result = new ArrayList<>();
        backtrack(result, new ArrayList<>(), s, 0);
        return result;
    }
    
    private void backtrack(List<String> result, List<String> path, String s, int start) {
        if (path.size() == 4) {
            if (start == s.length()) {
                result.add(String.join(".", path));
            }
            return;
        }
        
        for (int i = start; i < Math.min(start + 3, s.length()); i++) {
            String segment = s.substring(start, i + 1);
            if ((segment.length() > 1 && segment.charAt(0) == '0') || Integer.parseInt(segment) > 255) {
                continue;
            }
            path.add(segment);
            backtrack(result, path, s, i + 1);
            path.remove(path.size() - 1);
        }
    }
}