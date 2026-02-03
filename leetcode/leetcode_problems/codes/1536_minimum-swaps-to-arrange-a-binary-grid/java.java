/**
 * Problem: Minimum Swaps to Arrange a Binary Grid
 * Difficulty: Medium
 * Tags: array, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class Solution {
    public int minSwaps(int[][] grid) {
        int n = grid.length;
        List<Integer> trailingZeros = new ArrayList<>();
        
        for (int[] row : grid) {
            int count = 0;
            for (int i = n - 1; i >= 0; i--) {
                if (row[i] == 0) {
                    count++;
                } else {
                    break;
                }
            }
            trailingZeros.add(count);
        }
        
        int swaps = 0;
        for (int i = 0; i < n; i++) {
            int required = n - 1 - i;
            if (trailingZeros.get(i) >= required) {
                continue;
            }
            
            boolean found = false;
            for (int j = i + 1; j < n; j++) {
                if (trailingZeros.get(j) >= required) {
                    found = true;
                    swaps += j - i;
                    int temp = trailingZeros.get(j);
                    for (int k = j; k > i; k--) {
                        trailingZeros.set(k, trailingZeros.get(k - 1));
                    }
                    trailingZeros.set(i, temp);
                    break;
                }
            }
            
            if (!found) {
                return -1;
            }
        }
        
        return swaps;
    }
}