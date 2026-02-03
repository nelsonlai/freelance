"""
Problem: Decode XORed Permutation
Difficulty: Medium
Tags: array, bit manipulation

Approach: XOR all numbers 1..n to get first element, then decode rest
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def decode(self, encoded: List[int]) -> List[int]:
        n = len(encoded) + 1
        total_xor = 0
        for i in range(1, n + 1):
            total_xor ^= i
        
        # XOR of all encoded (even indices)
        encoded_xor = 0
        for i in range(1, len(encoded), 2):
            encoded_xor ^= encoded[i]
        
        # First element
        first = total_xor ^ encoded_xor
        result = [first]
        
        # Decode rest
        for num in encoded:
            result.append(result[-1] ^ num)
        
        return result