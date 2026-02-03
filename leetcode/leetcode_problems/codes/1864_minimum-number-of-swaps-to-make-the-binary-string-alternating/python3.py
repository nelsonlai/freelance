"""
Problem: Minimum Number of Swaps to Make the Binary String Alternating
Difficulty: Medium
Tags: string, greedy

Approach: Try both patterns (0-start, 1-start), count mismatches
Time Complexity: O(n) where n is length
Space Complexity: O(1)
"""

class Solution:
    def minSwaps(self, s: str) -> int:
        count0 = s.count('0')
        count1 = s.count('1')
        
        if abs(count0 - count1) > 1:
            return -1
        
        def count_mismatches(pattern):
            mismatches = 0
            for i, char in enumerate(s):
                if char != pattern[i % 2]:
                    mismatches += 1
            return mismatches // 2
        
        if count0 == count1:
            return min(count_mismatches('01'), count_mismatches('10'))
        elif count0 > count1:
            return count_mismatches('01')
        else:
            return count_mismatches('10')