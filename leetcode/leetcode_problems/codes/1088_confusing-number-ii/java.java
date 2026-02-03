/**
 * Problem: Confusing Number II
 * Difficulty: Hard
 * Tags: math
 * 
 * Approach: DFS to generate all valid confusing numbers, count those that rotate differently
 * Time Complexity: O(5^log10(n))
 * Space Complexity: O(log n) for recursion
 */

import java.util.*;

class Solution {
    private int count = 0;
    private static final int[] VALID_DIGITS = {0, 1, 6, 8, 9};
    private static final Map<Integer, Integer> ROTATE_MAP = new HashMap<>();
    
    static {
        ROTATE_MAP.put(0, 0);
        ROTATE_MAP.put(1, 1);
        ROTATE_MAP.put(6, 9);
        ROTATE_MAP.put(8, 8);
        ROTATE_MAP.put(9, 6);
    }
    
    public int confusingNumberII(int n) {
        dfs(0, n);
        return count;
    }
    
    private void dfs(long num, int n) {
        if (num > n) {
            return;
        }
        if (num > 0 && isConfusing(num)) {
            count++;
        }
        
        for (int digit : VALID_DIGITS) {
            if (num == 0 && digit == 0) {
                continue;
            }
            dfs(num * 10 + digit, n);
        }
    }
    
    private boolean isConfusing(long num) {
        long rotated = 0;
        long original = num;
        while (num > 0) {
            int digit = (int) (num % 10);
            if (!ROTATE_MAP.containsKey(digit)) {
                return false;
            }
            rotated = rotated * 10 + ROTATE_MAP.get(digit);
            num /= 10;
        }
        return rotated != original;
    }
}