"""
Problem: XOR Queries of a Subarray
Difficulty: Medium
Tags: array

Approach: Prefix XOR - XOR has property that prefix[i] XOR prefix[j] = XOR of arr[i:j]
Time Complexity: O(n + m) where n is arr length, m is queries length
Space Complexity: O(n) for prefix array
"""

class Solution:
    def xorQueries(self, arr: List[int], queries: List[List[int]]) -> List[int]:
        n = len(arr)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] ^ arr[i]
        
        result = []
        for left, right in queries:
            result.append(prefix[right + 1] ^ prefix[left])
        
        return result