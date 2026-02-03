"""
Problem: Count Triplets That Can Form Two Arrays of Equal XOR
Difficulty: Medium
Tags: array, math, hash

Approach: If a[i]^...^a[j-1] == a[j]^...^a[k], then prefix[i] == prefix[k+1]
Time Complexity: O(n^2) where n is length of arr
Space Complexity: O(n) for prefix
"""

class Solution:
    def countTriplets(self, arr: List[int]) -> int:
        n = len(arr)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] ^ arr[i]
        
        count = 0
        for i in range(n):
            for k in range(i + 1, n):
                if prefix[i] == prefix[k + 1]:
                    count += k - i
        
        return count