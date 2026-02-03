/**
 * Problem: Minimum Space Wasted From Packaging
 * Difficulty: Hard
 * Tags: array, sort, search, binary search
 * 
 * Approach: Sort packages, for each supplier try all boxes, use binary search
 * Time Complexity: O(n log n + m * (k log k + n log k)) where n is packages, m is suppliers, k is boxes
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    private static final int MOD = 1000000007;
    
    public int minWastedSpace(int[] packages, int[][] boxes) {
        Arrays.sort(packages);
        long total = 0;
        for (int p : packages) {
            total += p;
        }
        
        long result = Long.MAX_VALUE;
        
        for (int[] supplierBoxes : boxes) {
            Arrays.sort(supplierBoxes);
            if (supplierBoxes[supplierBoxes.length - 1] < packages[packages.length - 1]) {
                continue;
            }
            
            long wasted = 0;
            int prev = 0;
            
            for (int box : supplierBoxes) {
                int idx = Arrays.binarySearch(packages, box);
                if (idx < 0) {
                    idx = -idx - 1;
                } else {
                    while (idx < packages.length && packages[idx] == box) {
                        idx++;
                    }
                }
                
                if (idx > prev) {
                    wasted += (long) box * (idx - prev);
                    prev = idx;
                    if (prev == packages.length) {
                        break;
                    }
                }
            }
            
            if (prev == packages.length) {
                result = Math.min(result, wasted - total);
            }
        }
        
        return result == Long.MAX_VALUE ? -1 : (int)(result % MOD);
    }
}