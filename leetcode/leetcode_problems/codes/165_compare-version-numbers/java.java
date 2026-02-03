/**
 * Problem: Compare Version Numbers
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int compareVersion(String version1, String version2) {
        String[] v1Parts = version1.split("\\.");
        String[] v2Parts = version2.split("\\.");
        
        int maxLen = Math.max(v1Parts.length, v2Parts.length);
        
        for (int i = 0; i < maxLen; i++) {
            int v1 = (i < v1Parts.length) ? Integer.parseInt(v1Parts[i]) : 0;
            int v2 = (i < v2Parts.length) ? Integer.parseInt(v2Parts[i]) : 0;
            
            if (v1 > v2) {
                return 1;
            } else if (v1 < v2) {
                return -1;
            }
        }
        
        return 0;
    }
}