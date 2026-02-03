/**
 * Problem: Replace All ?'s to Avoid Consecutive Repeating Characters
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String modifyString(String s) {
        char[] result = s.toCharArray();
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            if (result[i] == '?') {
                for (char c : "abc".toCharArray()) {
                    if ((i == 0 || result[i-1] != c) && (i == n-1 || result[i+1] != c)) {
                        result[i] = c;
                        break;
                    }
                }
            }
        }
        
        return new String(result);
    }
}