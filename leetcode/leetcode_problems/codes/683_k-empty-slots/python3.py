"""
Problem: K Empty Slots
Difficulty: Hard
Tags: array, tree, queue, heap

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def kEmptySlots(self, bulbs: List[int], k: int) -> int:
        n = len(bulbs)
        days = [0] * n
        for day, pos in enumerate(bulbs, 1):
            days[pos - 1] = day
        
        left, right = 0, k + 1
        result = float('inf')
        
        while right < n:
            max_day = max(days[left], days[right])
            valid = True
            
            for i in range(left + 1, right):
                if days[i] < max_day:
                    valid = False
                    break
            
            if valid:
                result = min(result, max_day)
            
            left = right
            right = left + k + 1
        
        return result if result != float('inf') else -1