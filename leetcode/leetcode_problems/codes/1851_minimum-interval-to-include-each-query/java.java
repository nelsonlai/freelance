/**
 * Problem: Minimum Interval to Include Each Query
 * Difficulty: Hard
 * Tags: array, sort, search, queue, heap
 * 
 * Approach: Sort intervals and queries, use heap to track active intervals
 * Time Complexity: O(n log n + q log q) where n is intervals, q is queries
 * Space Complexity: O(n + q)
 */

import java.util.*;

class Solution {
    public int[] minInterval(int[][] intervals, int[] queries) {
        Arrays.sort(intervals, (a, b) -> Integer.compare(a[0], b[0]));
        
        int[][] sortedQueries = new int[queries.length][2];
        for (int i = 0; i < queries.length; i++) {
            sortedQueries[i] = new int[]{queries[i], i};
        }
        Arrays.sort(sortedQueries, (a, b) -> Integer.compare(a[0], b[0]));
        
        int[] result = new int[queries.length];
        Arrays.fill(result, -1);
        
        PriorityQueue<int[]> heap = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));
        int i = 0;
        
        for (int[] query : sortedQueries) {
            int q = query[0];
            int idx = query[1];
            
            while (i < intervals.length && intervals[i][0] <= q) {
                int size = intervals[i][1] - intervals[i][0] + 1;
                heap.offer(new int[]{size, intervals[i][1]});
                i++;
            }
            
            while (!heap.isEmpty() && heap.peek()[1] < q) {
                heap.poll();
            }
            
            if (!heap.isEmpty()) {
                result[idx] = heap.peek()[0];
            }
        }
        
        return result;
    }
}