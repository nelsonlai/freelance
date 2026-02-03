/**
 * Problem: Two City Scheduling
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort by difference (costA - costB), send first n/2 to A, rest to B
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(1)
 */

import java.util.*;

class Solution {
    public int twoCitySchedCost(int[][] costs) {
        Arrays.sort(costs, (a, b) -> (a[0] - a[1]) - (b[0] - b[1]));
        int n = costs.length / 2;
        int result = 0;
        
        for (int i = 0; i < n; i++) {
            result += costs[i][0] + costs[i + n][1];
        }
        
        return result;
    }
}