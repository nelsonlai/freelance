"""
Problem: Count of Range Sum
Difficulty: Hard
Tags: array, tree, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        def mergeSort(prefix, left, right):
            if left >= right:
                return 0
            
            mid = (left + right) // 2
            count = mergeSort(prefix, left, mid) + mergeSort(prefix, mid + 1, right)
            
            i = j = mid + 1
            for k in range(left, mid + 1):
                while i <= right and prefix[i] - prefix[k] < lower:
                    i += 1
                while j <= right and prefix[j] - prefix[k] <= upper:
                    j += 1
                count += j - i
            
            prefix[left:right + 1] = sorted(prefix[left:right + 1])
            return count
        
        prefix = [0]
        for num in nums:
            prefix.append(prefix[-1] + num)
        
        return mergeSort(prefix, 0, len(prefix) - 1)