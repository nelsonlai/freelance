"""
Problem: Odd Even Jump
Difficulty: Hard
Tags: array, dp, sort, stack

Approach: DP with monotonic stack - find next greater/lesser element for each position
Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for DP and stack
"""

from sortedcontainers import SortedList

class Solution:
    def oddEvenJumps(self, arr: List[int]) -> int:
        n = len(arr)
        next_higher = [0] * n
        next_lower = [0] * n
        
        # Build next_higher and next_lower using sorted list
        sorted_list = SortedList()
        for i in range(n - 1, -1, -1):
            idx = sorted_list.bisect_left((arr[i], i))
            if idx < len(sorted_list):
                next_higher[i] = sorted_list[idx][1]
            else:
                next_higher[i] = -1
            
            idx = sorted_list.bisect_left((arr[i], -1))
            if idx > 0:
                next_lower[i] = sorted_list[idx - 1][1]
            else:
                next_lower[i] = -1
            
            sorted_list.add((arr[i], i))
        
        # DP: odd[i] = can reach end from i with odd jump, even[i] = can reach with even jump
        odd = [False] * n
        even = [False] * n
        odd[n - 1] = even[n - 1] = True
        
        for i in range(n - 2, -1, -1):
            if next_higher[i] != -1:
                odd[i] = even[next_higher[i]]
            if next_lower[i] != -1:
                even[i] = odd[next_lower[i]]
        
        return sum(odd)