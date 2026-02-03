"""
Problem: Kth Smallest Instructions
Difficulty: Hard
Tags: array, string, dp, math, combinatorics

Approach: Greedy - at each step, decide H or V based on number of paths starting with H
Time Complexity: O(r * c) where r, c are destination coordinates
Space Complexity: O(r + c)
"""

import math

class Solution:
    def kthSmallestPath(self, destination: List[int], k: int) -> str:
        v, h = destination[0], destination[1]
        result = []
        
        for i in range(h + v):
            if h == 0:
                result.append('V')
                v -= 1
            elif v == 0:
                result.append('H')
                h -= 1
            else:
                # Count paths starting with H
                paths_with_h = math.comb(h + v - 1, v)
                if k <= paths_with_h:
                    result.append('H')
                    h -= 1
                else:
                    result.append('V')
                    k -= paths_with_h
                    v -= 1
        
        return ''.join(result)