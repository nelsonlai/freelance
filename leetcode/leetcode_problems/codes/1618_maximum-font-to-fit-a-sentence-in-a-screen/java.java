/**
 * Problem: Maximum Font to Fit a Sentence in a Screen
 * Difficulty: Medium
 * Tags: array, string, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

/**
 * // This is the FontInfo's API interface.
 * // You should not implement it, or speculate about its implementation
 * interface FontInfo {
 *     // Return the width of char ch when fontSize is used.
 *     public int getWidth(int fontSize, char ch);
 *     // Return Height of any char when fontSize is used.
 *     public int getHeight(int fontSize);
 * }
 */
class Solution {
    public int maxFont(String text, int w, int h, int[] fonts, FontInfo fontInfo) {
        Arrays.sort(fonts);
        int left = 0, right = fonts.length - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = (left + right) / 2;
            int fontSize = fonts[mid];
            
            if (fontInfo.getHeight(fontSize) > h) {
                right = mid - 1;
                continue;
            }
            
            int totalWidth = 0;
            for (char ch : text.toCharArray()) {
                totalWidth += fontInfo.getWidth(fontSize, ch);
            }
            
            if (totalWidth <= w) {
                result = fontSize;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
}