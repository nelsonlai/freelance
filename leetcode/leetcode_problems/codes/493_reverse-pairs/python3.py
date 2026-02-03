"""
Problem: Reverse Pairs
Difficulty: Hard
Tags: array, tree, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def reversePairs(self, nums: List[int]) -> int:
        def merge_sort(left, right):
            if left >= right:
                return 0
            
            mid = (left + right) // 2
            count = merge_sort(left, mid) + merge_sort(mid + 1, right)
            
            j = mid + 1
            for i in range(left, mid + 1):
                while j <= right and nums[i] > 2 * nums[j]:
                    j += 1
                count += j - (mid + 1)
            
            nums[left:right+1] = sorted(nums[left:right+1])
            return count
        
        return merge_sort(0, len(nums) - 1)