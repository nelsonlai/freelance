"""
Problem: Incremental Memory Leak
Difficulty: Medium
Tags: array, math

Approach: Simulate memory leak, allocate to larger memory block
Time Complexity: O(sqrt(memory1 + memory2))
Space Complexity: O(1)
"""

class Solution:
    def memLeak(self, memory1: int, memory2: int) -> List[int]:
        time = 1
        
        while True:
            if memory1 >= memory2:
                if memory1 < time:
                    return [time, memory1, memory2]
                memory1 -= time
            else:
                if memory2 < time:
                    return [time, memory1, memory2]
                memory2 -= time
            time += 1