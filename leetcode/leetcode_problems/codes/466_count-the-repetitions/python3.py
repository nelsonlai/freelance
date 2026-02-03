"""
Problem: Count The Repetitions
Difficulty: Hard
Tags: string, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def getMaxRepetitions(self, s1: str, n1: int, s2: str, n2: int) -> int:
        if not s2:
            return 0
        
        s1_count = 0
        s2_count = 0
        index = 0
        recall = {}
        
        while s1_count < n1:
            for char in s1:
                if char == s2[index]:
                    index += 1
                    if index == len(s2):
                        s2_count += 1
                        index = 0
            
            s1_count += 1
            
            if index in recall:
                prev_s1_count, prev_s2_count = recall[index]
                cycle_s1 = s1_count - prev_s1_count
                cycle_s2 = s2_count - prev_s2_count
                remaining_cycles = (n1 - s1_count) // cycle_s1
                s1_count += remaining_cycles * cycle_s1
                s2_count += remaining_cycles * cycle_s2
            else:
                recall[index] = (s1_count, s2_count)
        
        return s2_count // n2