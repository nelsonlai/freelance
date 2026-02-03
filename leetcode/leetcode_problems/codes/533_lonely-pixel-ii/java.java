/**
 * Problem: Lonely Pixel II
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findBlackPixel(char[][] picture, int target) {
        int m = picture.length, n = picture[0].length;
        Map<Integer, Integer> rowCount = new HashMap<>();
        Map<Integer, Integer> colCount = new HashMap<>();
        Map<String, Integer> rowPatterns = new HashMap<>();
        
        for (int i = 0; i < m; i++) {
            StringBuilder pattern = new StringBuilder();
            for (int j = 0; j < n; j++) {
                pattern.append(picture[i][j]);
                if (picture[i][j] == 'B') {
                    rowCount.put(i, rowCount.getOrDefault(i, 0) + 1);
                    colCount.put(j, colCount.getOrDefault(j, 0) + 1);
                }
            }
            String patternStr = pattern.toString();
            rowPatterns.put(patternStr, rowPatterns.getOrDefault(patternStr, 0) + 1);
        }
        
        int result = 0;
        for (int j = 0; j < n; j++) {
            if (colCount.getOrDefault(j, 0) == target) {
                for (int i = 0; i < m; i++) {
                    if (picture[i][j] == 'B') {
                        StringBuilder pattern = new StringBuilder();
                        for (int k = 0; k < n; k++) {
                            pattern.append(picture[i][k]);
                        }
                        String patternStr = pattern.toString();
                        if (rowCount.get(i) == target && rowPatterns.get(patternStr) == target) {
                            result += target;
                        }
                        break;
                    }
                }
            }
        }
        
        return result;
    }
}