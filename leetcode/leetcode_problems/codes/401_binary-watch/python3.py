"""
Problem: Binary Watch
Difficulty: Easy
Tags: general

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def readBinaryWatch(self, turnedOn: int) -> List[str]:
        result = []
        
        for hour in range(12):
            for minute in range(60):
                if bin(hour).count('1') + bin(minute).count('1') == turnedOn:
                    result.append(f"{hour}:{minute:02d}")
        
        return result