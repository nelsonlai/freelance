"""
Problem: Rearrange String k Distance Apart
Difficulty: Hard
Tags: string, greedy, hash, sort, queue, heap

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import Counter
import heapq

class Solution:
    def rearrangeString(self, s: str, k: int) -> str:
        if k == 0:
            return s
        
        count = Counter(s)
        heap = [(-freq, char) for char, freq in count.items()]
        heapq.heapify(heap)
        
        result = []
        wait_queue = []
        
        while heap:
            freq, char = heapq.heappop(heap)
            result.append(char)
            
            if freq + 1 < 0:
                wait_queue.append((freq + 1, char))
            
            if len(wait_queue) >= k:
                freq, char = wait_queue.pop(0)
                heapq.heappush(heap, (freq, char))
        
        if len(wait_queue) > 0:
            return ""
        
        return ''.join(result) if len(result) == len(s) else ""