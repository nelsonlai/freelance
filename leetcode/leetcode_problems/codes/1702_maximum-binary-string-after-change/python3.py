"""
Problem: Maximum Binary String After Change
Difficulty: Medium
Tags: string, greedy

Approach: Greedy - move all zeros to the left, then convert "00" to "10" to maximize
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maximumBinaryString(self, binary: str) -> str:
        if '0' not in binary:
            return binary
        
        zeros = binary.count('0')
        first_zero = binary.index('0')
        
        # After operations, we'll have zeros-1 ones, then one zero, then rest ones
        result = ['1'] * len(binary)
        result[first_zero + zeros - 1] = '0'
        
        return ''.join(result)