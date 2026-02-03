/*
 * Problem: Find the Index of the First Occurrence in a String
 * Difficulty: Easy
 * Tags: array, string, stack
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

public class Solution {
    public int StrStr(string haystack, string needle) {
        if (string.IsNullOrEmpty(needle)) {
            return 0;
        }
        
        int n = haystack.Length;
        int m = needle.Length;
        
        for (int i = 0; i <= n - m; i++) {
            if (haystack.Substring(i, m) == needle) {
                return i;
            }
        }
        
        return -1;
    }
}