/**
 * Problem: License Key Formatting
 * Difficulty: Easy
 * Tags: string
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public String licenseKeyFormatting(String s, int k) {
        s = s.replace("-", "").toUpperCase();
        int n = s.length();
        int firstGroup = n % k != 0 ? n % k : k;
        StringBuilder result = new StringBuilder(s.substring(0, firstGroup));
        
        for (int i = firstGroup; i < n; i += k) {
            result.append("-").append(s.substring(i, i + k));
        }
        
        return result.toString();
    }
}