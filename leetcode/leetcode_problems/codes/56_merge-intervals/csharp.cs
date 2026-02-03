/*
 * Problem: Merge Intervals
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;
using System.Linq;

public class Solution {
    public int[][] Merge(int[][] intervals) {
        if (intervals.Length == 0) {
            return new int[0][];
        }
        
        var sorted = intervals.OrderBy(x => x[0]).ToArray();
        List<int[]> result = new List<int[]>();
        result.Add(sorted[0]);
        
        for (int i = 1; i < sorted.Length; i++) {
            if (sorted[i][0] <= result[result.Count - 1][1]) {
                result[result.Count - 1][1] = System.Math.Max(result[result.Count - 1][1], sorted[i][1]);
            } else {
                result.Add(sorted[i]);
            }
        }
        
        return result.ToArray();
    }
}