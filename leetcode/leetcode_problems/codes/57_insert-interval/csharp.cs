/*
 * Problem: Insert Interval
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

using System.Collections.Generic;

public class Solution {
    public int[][] Insert(int[][] intervals, int[] newInterval) {
        List<int[]> result = new List<int[]>();
        int i = 0;
        
        // Add all intervals before newInterval
        while (i < intervals.Length && intervals[i][1] < newInterval[0]) {
            result.Add(intervals[i]);
            i++;
        }
        
        // Merge overlapping intervals
        while (i < intervals.Length && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = System.Math.Min(newInterval[0], intervals[i][0]);
            newInterval[1] = System.Math.Max(newInterval[1], intervals[i][1]);
            i++;
        }
        
        result.Add(newInterval);
        
        // Add remaining intervals
        while (i < intervals.Length) {
            result.Add(intervals[i]);
            i++;
        }
        
        return result.ToArray();
    }
}