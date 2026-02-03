"""
Problem: Minimum Adjacent Swaps to Reach the Kth Smallest Number
Difficulty: Medium
Tags: array, string, greedy

Approach: Find kth permutation, count swaps needed to transform original
Time Complexity: O(n^2) where n is length
Space Complexity: O(n)
"""

class Solution:
    def getMinSwaps(self, num: str, k: int) -> int:
        def next_permutation(arr):
            i = len(arr) - 2
            while i >= 0 and arr[i] >= arr[i+1]:
                i -= 1
            if i < 0:
                return False
            
            j = len(arr) - 1
            while arr[j] <= arr[i]:
                j -= 1
            
            arr[i], arr[j] = arr[j], arr[i]
            arr[i+1:] = reversed(arr[i+1:])
            return True
        
        original = list(num)
        target = list(num)
        
        for _ in range(k):
            next_permutation(target)
        
        # Count swaps needed
        result = 0
        for i in range(len(original)):
            if original[i] != target[i]:
                j = i + 1
                while original[j] != target[i]:
                    j += 1
                result += j - i
                original[i:j+1] = [original[j]] + original[i:j]
        
        return result