"""
Problem: Minimum Interval to Include Each Query
Difficulty: Hard
Tags: array, sort, search, queue, heap

Approach: Sort intervals and queries, use heap to track active intervals
Time Complexity: O(n log n + q log q) where n is intervals, q is queries
Space Complexity: O(n + q)
"""

import heapq

class Solution:
    def minInterval(self, intervals: List[List[int]], queries: List[int]) -> List[int]:
        intervals.sort()
        sorted_queries = sorted((q, i) for i, q in enumerate(queries))
        
        result = [-1] * len(queries)
        heap = []  # (size, end)
        i = 0
        
        for query, idx in sorted_queries:
            # Add all intervals that start <= query
            while i < len(intervals) and intervals[i][0] <= query:
                start, end = intervals[i]
                heapq.heappush(heap, (end - start + 1, end))
                i += 1
            
            # Remove intervals that end < query
            while heap and heap[0][1] < query:
                heapq.heappop(heap)
            
            # Get minimum size
            if heap:
                result[idx] = heap[0][0]
        
        return result