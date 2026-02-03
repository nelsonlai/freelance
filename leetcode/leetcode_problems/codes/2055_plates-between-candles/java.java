/**
 * Problem: Plates Between Candles
 * Difficulty: Medium
 * Tags: array, string, prefix sum, binary search
 * 
 * Approach: Use prefix sum for plates, binary search for nearest candles
 * Time Complexity: O(n + q log n) where n is length, q is queries
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int[] platesBetweenCandles(String s, int[][] queries) {
        int n = s.length();
        // Store positions of candles
        List<Integer> candles = new ArrayList<>();
        // Prefix sum of plates
        int[] prefixPlates = new int[n + 1];
        
        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);
            if (c == '|') {
                candles.add(i);
            }
            prefixPlates[i + 1] = prefixPlates[i] + (c == '*' ? 1 : 0);
        }
        
        int[] result = new int[queries.length];
        
        for (int idx = 0; idx < queries.length; idx++) {
            int left = queries[idx][0];
            int right = queries[idx][1];
            
            // Find first candle >= left
            int leftIdx = Collections.binarySearch(candles, left);
            if (leftIdx < 0) {
                leftIdx = -(leftIdx + 1);
            }
            
            // Find last candle <= right
            int rightIdx = Collections.binarySearch(candles, right);
            if (rightIdx < 0) {
                rightIdx = -(rightIdx + 1) - 1;
            }
            
            if (leftIdx < candles.size() && rightIdx >= leftIdx) {
                int leftCandle = candles.get(leftIdx);
                int rightCandle = candles.get(rightIdx);
                // Count plates between candles
                result[idx] = prefixPlates[rightCandle + 1] - prefixPlates[leftCandle];
            } else {
                result[idx] = 0;
            }
        }
        
        return result;
    }
}