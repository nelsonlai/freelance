"""
Problem: Minimum Time to Build Blocks
Difficulty: Hard
Tags: array, greedy, math, queue, heap

Approach: Use min heap - always split worker with longest remaining time
Time Complexity: O(n log n) where n is number of blocks
Space Complexity: O(n) for heap
"""

class Solution:
    def minBuildTime(self, blocks: List[int], split: int) -> int:
        import heapq
        
        heapq.heapify(blocks)
        
        while len(blocks) > 1:
            # Get two smallest blocks
            first = heapq.heappop(blocks)
            second = heapq.heappop(blocks)
            # Split worker to build both, add split time to second
            heapq.heappush(blocks, max(first, second) + split)
        
        return blocks[0]