"""
Problem: Decode XORed Array
Difficulty: Easy
Tags: array, bit manipulation

Approach: If encoded[i] = arr[i] XOR arr[i+1], then arr[i+1] = arr[i] XOR encoded[i]
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def decode(self, encoded: List[int], first: int) -> List[int]:
        result = [first]
        for num in encoded:
            result.append(result[-1] ^ num)
        return result