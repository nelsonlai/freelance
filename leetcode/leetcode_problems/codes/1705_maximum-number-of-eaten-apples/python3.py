"""
Problem: Maximum Number of Eaten Apples
Difficulty: Medium
Tags: array, greedy, queue, heap

Approach: Use min heap to track apples by expiration date, eat earliest expiring first
Time Complexity: O(n log n) where n is days
Space Complexity: O(n) for heap
"""

import heapq

class Solution:
    def eatenApples(self, apples: List[int], days: List[int]) -> int:
        heap = []
        result = 0
        n = len(apples)
        
        for i in range(n):
            # Add new apples
            if apples[i] > 0:
                heapq.heappush(heap, (i + days[i], apples[i]))
            
            # Remove expired apples
            while heap and heap[0][0] <= i:
                heapq.heappop(heap)
            
            # Eat one apple
            if heap:
                expiry, count = heapq.heappop(heap)
                result += 1
                if count > 1:
                    heapq.heappush(heap, (expiry, count - 1))
        
        # Continue eating after day n
        day = n
        while heap:
            # Remove expired
            while heap and heap[0][0] <= day:
                heapq.heappop(heap)
            
            if not heap:
                break
            
            # Eat one apple
            expiry, count = heapq.heappop(heap)
            result += 1
            if count > 1:
                heapq.heappush(heap, (expiry, count - 1))
            day += 1
        
        return result