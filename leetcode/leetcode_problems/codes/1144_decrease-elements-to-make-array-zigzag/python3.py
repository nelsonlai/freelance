"""
Problem: Decrease Elements To Make Array Zigzag
Difficulty: Medium
Tags: array, greedy

Approach: Try two patterns - even indices greater or odd indices greater, take minimum moves
Time Complexity: O(n) where n is the length of nums
Space Complexity: O(1)
"""

class Solution:
    def movesToMakeZigzag(self, nums: List[int]) -> int:
        def calculate_moves(pattern):
            moves = 0
            temp_nums = nums[:]
            for i in range(len(temp_nums)):
                should_be_high = (i % 2 == pattern)
                if should_be_high:
                    # This index should be higher than neighbors
                    if i > 0 and temp_nums[i] <= temp_nums[i-1]:
                        moves += temp_nums[i-1] - temp_nums[i] + 1
                        temp_nums[i-1] = temp_nums[i] - 1
                    if i < len(temp_nums) - 1 and temp_nums[i] <= temp_nums[i+1]:
                        moves += temp_nums[i+1] - temp_nums[i] + 1
                        temp_nums[i+1] = temp_nums[i] - 1
            return moves
        
        return min(calculate_moves(0), calculate_moves(1))