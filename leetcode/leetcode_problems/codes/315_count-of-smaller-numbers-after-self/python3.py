"""
Problem: Count of Smaller Numbers After Self
Difficulty: Hard
Tags: array, tree, sort, search

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

class Solution:
    def countSmaller(self, nums: List[int]) -> List[int]:
        def mergeSort(enum):
            half = len(enum) // 2
            if half:
                left, right = mergeSort(enum[:half]), mergeSort(enum[half:])
                for i in range(len(enum) - 1, -1, -1):
                    if not right or left and left[-1][1] > right[-1][1]:
                        smaller[left[-1][0]] += len(right)
                        enum[i] = left.pop()
                    else:
                        enum[i] = right.pop()
            return enum
        
        smaller = [0] * len(nums)
        mergeSort(list(enumerate(nums)))
        return smaller