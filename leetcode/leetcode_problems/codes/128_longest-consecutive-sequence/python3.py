"""
Problem: Longest Consecutive Sequence
Difficulty: Medium
Tags: array, graph, hash, sort

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        numSet = set(nums)
        maxLength = 0
        
        for num in numSet:
            if num - 1 not in numSet:
                currentNum = num
                currentLength = 1
                
                while currentNum + 1 in numSet:
                    currentNum += 1
                    currentLength += 1
                
                maxLength = max(maxLength, currentLength)
        
        return maxLength