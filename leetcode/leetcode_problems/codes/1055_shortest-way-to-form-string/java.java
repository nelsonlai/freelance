/**
 * Problem: Shortest Way to Form String
 * Difficulty: Medium
 * Tags: array, string, greedy, search
 * 
 * Approach: Greedy - try to match as many characters as possible from source in each pass
 * Time Complexity: O(m * n) where m is source length, n is target length
 * Space Complexity: O(1)
 */

class Solution {
    public int shortestWay(String source, String target) {
        int result = 0;
        int targetIdx = 0;
        
        while (targetIdx < target.length()) {
            boolean found = false;
            for (char c : source.toCharArray()) {
                if (targetIdx < target.length() && target.charAt(targetIdx) == c) {
                    targetIdx++;
                    found = true;
                }
            }
            
            if (!found) {
                return -1;
            }
            result++;
        }
        
        return result;
    }
}