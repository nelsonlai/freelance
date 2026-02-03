"""
Problem: Maximum XOR With an Element From Array
Difficulty: Hard
Tags: array, trie, bit manipulation

Approach: Use Trie to store numbers, for each query find max XOR with numbers <= limit
Time Complexity: O(n * 32 + q * 32) where n is nums, q is queries
Space Complexity: O(n * 32) for trie
"""

class TrieNode:
    def __init__(self):
        self.children = [None, None]
        self.min_val = float('inf')

class Solution:
    def maximizeXor(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        root = TrieNode()
        
        # Build trie
        for num in nums:
            node = root
            node.min_val = min(node.min_val, num)
            for i in range(31, -1, -1):
                bit = (num >> i) & 1
                if not node.children[bit]:
                    node.children[bit] = TrieNode()
                node = node.children[bit]
                node.min_val = min(node.min_val, num)
        
        result = []
        for x, limit in queries:
            node = root
            if node.min_val > limit:
                result.append(-1)
                continue
            
            max_xor = 0
            for i in range(31, -1, -1):
                bit = (x >> i) & 1
                desired = 1 - bit
                
                # Try to go to desired bit if it exists and min_val <= limit
                if node.children[desired] and node.children[desired].min_val <= limit:
                    max_xor |= (1 << i)
                    node = node.children[desired]
                else:
                    node = node.children[bit]
            
            result.append(max_xor)
        
        return result