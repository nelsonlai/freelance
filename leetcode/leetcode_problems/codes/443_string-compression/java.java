/**
 * Problem: String Compression
 * Difficulty: Medium
 * Tags: array, string
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

class Solution {
    public int compress(char[] chars) {
        int write = 0;
        int read = 0;
        
        while (read < chars.length) {
            char currentChar = chars[read];
            int count = 0;
            
            while (read < chars.length && chars[read] == currentChar) {
                read++;
                count++;
            }
            
            chars[write++] = currentChar;
            
            if (count > 1) {
                String countStr = String.valueOf(count);
                for (char c : countStr.toCharArray()) {
                    chars[write++] = c;
                }
            }
        }
        
        return write;
    }
}