/**
 * Problem: Eliminate Maximum Number of Monsters
 * Difficulty: Medium
 * Tags: array, greedy, sort
 * 
 * Approach: Sort by arrival time, eliminate one per minute
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n)
 */

import java.util.*;

class Solution {
    public int eliminateMaximum(int[] dist, int[] speed) {
        int n = dist.length;
        double[] arrivalTimes = new double[n];
        for (int i = 0; i < n; i++) {
            arrivalTimes[i] = (double) dist[i] / speed[i];
        }
        Arrays.sort(arrivalTimes);
        
        for (int i = 0; i < n; i++) {
            if (arrivalTimes[i] <= i) {
                return i;
            }
        }
        
        return n;
    }
}