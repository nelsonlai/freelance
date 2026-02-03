"""
Problem: Count Pairs With XOR in a Range
Difficulty: Hard
Tags: array, trie, bit manipulation

Approach: Use Trie to count pairs with XOR < threshold
Time Complexity: O(n * 15) where 15 is max bits
Space Complexity: O(n * 15)
"""

class TrieNode:
    def __init__(self):
        self.count = 0
        self.children = [None, None]

class Solution:
    def countPairs(self, nums: List[int], low: int, high: int) -> int:
        def countLessThan(threshold):
            root = TrieNode()
            count = 0
            
            for num in nums:
                node = root
                for i in range(14, -1, -1):
                    bit = (num >> i) & 1
                    threshold_bit = (threshold >> i) & 1
                    
                    if threshold_bit == 1:
                        if node.children[bit]:
                            count += node.children[bit].count
                        if node.children[1 - bit]:
                            node = node.children[1 - bit]
                        else:
                            break
                    else:
                        if node.children[bit]:
                            node = node.children[bit]
                        else:
                            break
                else:
                    if node:
                        count += node.count
                
                # Insert current number
                node = root
                for i in range(14, -1, -1):
                    bit = (num >> i) & 1
                    if not node.children[bit]:
                        node.children[bit] = TrieNode()
                    node = node.children[bit]
                    node.count += 1
            
            return count
        
        return countLessThan(high + 1) - countLessThan(low)