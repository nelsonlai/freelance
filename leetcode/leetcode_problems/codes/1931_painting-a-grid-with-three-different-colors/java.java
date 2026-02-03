/**
 * Problem: Painting a Grid With Three Different Colors
 * Difficulty: Hard
 * Tags: dp, bitmask
 * 
 * Approach: DP with bitmask - track valid colorings for each column
 * Time Complexity: O(n * 3^m * m) where n is columns, m is rows
 * Space Complexity: O(3^m)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    private Map<Integer, List<Integer>> validColors;
    private int m;
    
    public int colorTheGrid(int m, int n) {
        this.m = m;
        validColors = new HashMap<>();
        
        return dp(0, -1, n);
    }
    
    private int dp(int col, int prevCol, int n) {
        if (col == n) {
            return 1;
        }
        
        List<Integer> valid = getValidColors(prevCol);
        long result = 0;
        for (int color : valid) {
            result = (result + dp(col + 1, color, n)) % MOD;
        }
        return (int) result;
    }
    
    private List<Integer> getValidColors(int prevCol) {
        if (validColors.containsKey(prevCol)) {
            return validColors.get(prevCol);
        }
        
        List<Integer> colors = new ArrayList<>();
        int maxMask = (int) Math.pow(3, m);
        
        for (int mask = 0; mask < maxMask; mask++) {
            boolean valid = true;
            int temp = mask;
            int prev = prevCol;
            
            for (int i = 0; i < m; i++) {
                int curr = temp % 3;
                if (prevCol != -1) {
                    int prevDigit = prev % 3;
                    if (curr == prevDigit) {
                        valid = false;
                        break;
                    }
                }
                if (i > 0) {
                    int prevTemp = (temp / 3) % 3;
                    if (curr == prevTemp) {
                        valid = false;
                        break;
                    }
                }
                temp /= 3;
                if (prevCol != -1) {
                    prev /= 3;
                }
            }
            
            if (valid) {
                colors.add(mask);
            }
        }
        
        validColors.put(prevCol, colors);
        return colors;
    }
}