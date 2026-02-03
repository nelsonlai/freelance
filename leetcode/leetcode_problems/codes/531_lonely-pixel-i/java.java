/**
 * Problem: Lonely Pixel I
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    public int findLonelyPixel(char[][] picture) {
        int m = picture.length, n = picture[0].length;
        Map<Integer, Integer> rowCount = new HashMap<>();
        Map<Integer, Integer> colCount = new HashMap<>();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (picture[i][j] == 'B') {
                    rowCount.put(i, rowCount.getOrDefault(i, 0) + 1);
                    colCount.put(j, colCount.getOrDefault(j, 0) + 1);
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (picture[i][j] == 'B' && rowCount.get(i) == 1 && colCount.get(j) == 1) {
                    result++;
                }
            }
        }
        
        return result;
    }
}