"""
Problem: Minimum Cost to Connect Sticks
Difficulty: Medium
Tags: array, greedy, queue, heap

Approach: Greedy with min heap - always connect two shortest sticks
Time Complexity: O(n log n) where n is number of sticks
Space Complexity: O(n) for heap
"""

class Solution:
    def connectSticks(self, sticks: List[int]) -> int:
        import heapq
        
        if len(sticks) <= 1:
            return 0
        
        heapq.heapify(sticks)
        total_cost = 0
        
        while len(sticks) > 1:
            first = heapq.heappop(sticks)
            second = heapq.heappop(sticks)
            cost = first + second
            total_cost += cost
            heapq.heappush(sticks, cost)
        
        return total_cost