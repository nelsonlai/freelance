"""
Problem: Create Maximum Number
Difficulty: Hard
Tags: array, greedy, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def maxNumber(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        def getMax(nums, k):
            stack = []
            drop = len(nums) - k
            for num in nums:
                while drop > 0 and stack and stack[-1] < num:
                    stack.pop()
                    drop -= 1
                stack.append(num)
            return stack[:k]
        
        def merge(nums1, nums2):
            result = []
            i = j = 0
            while i < len(nums1) or j < len(nums2):
                if i >= len(nums1):
                    result.append(nums2[j])
                    j += 1
                elif j >= len(nums2):
                    result.append(nums1[i])
                    i += 1
                elif nums1[i:] > nums2[j:]:
                    result.append(nums1[i])
                    i += 1
                else:
                    result.append(nums2[j])
                    j += 1
            return result
        
        result = []
        for i in range(max(0, k - len(nums2)), min(k, len(nums1)) + 1):
            candidate = merge(getMax(nums1, i), getMax(nums2, k - i))
            if candidate > result:
                result = candidate
        
        return result