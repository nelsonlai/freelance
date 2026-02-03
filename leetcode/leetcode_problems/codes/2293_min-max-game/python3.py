"""
Problem: Min Max Game
Difficulty: Easy
Tags: array

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def minMaxGame(self, nums: List[int]) -> int:
        while len(nums) > 1:
            new_nums = []
            for i in range(0, len(nums) // 2):
                if i % 2 == 0:
                    new_nums.append(min(nums[2 * i], nums[2 * i + 1]))
                else:
                    new_nums.append(max(nums[2 * i], nums[2 * i + 1]))
            nums = new_nums
        return nums[0]