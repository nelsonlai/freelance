"""
Problem: Minimum Possible Integer After at Most K Adjacent Swaps On Digits
Difficulty: Hard
Tags: string, tree, greedy

Approach: Greedy - for each position, find smallest digit within k swaps, move it to front
Time Complexity: O(n^2) where n is length of num
Space Complexity: O(n) for result
"""

class Solution:
    def minInteger(self, num: str, k: int) -> str:
        num_list = list(num)
        n = len(num_list)
        
        for i in range(n):
            if k <= 0:
                break
            
            min_digit = num_list[i]
            min_idx = i
            
            for j in range(i + 1, min(i + k + 1, n)):
                if num_list[j] < min_digit:
                    min_digit = num_list[j]
                    min_idx = j
            
            if min_idx > i:
                k -= (min_idx - i)
                num_list[i:min_idx+1] = [num_list[min_idx]] + num_list[i:min_idx]
        
        return ''.join(num_list)