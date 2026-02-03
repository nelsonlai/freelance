"""
Problem: Two Sum
Difficulty: Easy
Tags: array, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n)
Space Complexity: O(1) for hash map
"""
from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        seen = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in seen:
                return [seen[complement], i]
            seen[num] = i
        return []

if __name__ == "__main__":
    solution = Solution()
    print(solution.twoSum([2, 7, 11, 15], 9))
    print(solution.twoSum([3, 2, 5], 6))
    print(solution.twoSum([3, 3], 6))
    print(solution.twoSum([1, 2, 3, 4, 5], 10))
    print(solution.twoSum([1, 2, 3, 4, 5], 10))