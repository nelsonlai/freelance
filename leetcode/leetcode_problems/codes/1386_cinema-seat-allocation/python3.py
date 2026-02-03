"""
Problem: Cinema Seat Allocation
Difficulty: Medium
Tags: array, greedy, hash

Approach: Group reserved seats by row, check which 4-seat blocks are available
Time Complexity: O(m) where m is number of reserved seats
Space Complexity: O(m) for reserved map
"""

from collections import defaultdict

class Solution:
    def maxNumberOfFamilies(self, n: int, reservedSeats: List[List[int]]) -> int:
        reserved = defaultdict(set)
        for row, seat in reservedSeats:
            reserved[row].add(seat)
        
        result = 2 * n  # Maximum possible
        
        for row, seats in reserved.items():
            count = 0
            # Check left block (2-5)
            if not any(seat in seats for seat in [2, 3, 4, 5]):
                count += 1
            # Check middle block (4-7)
            if not any(seat in seats for seat in [4, 5, 6, 7]):
                count += 1
            # Check right block (6-9)
            if not any(seat in seats for seat in [6, 7, 8, 9]):
                count += 1
            
            if count == 0:
                result -= 2
            elif count == 1:
                result -= 1
        
        return result