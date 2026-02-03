"""
Problem: Largest Number After Mutating Substring
Difficulty: Medium
Tags: array, string, greedy

Approach: Greedily mutate substring where change[i] > digit
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def maximumNumber(self, num: str, change: List[int]) -> str:
        num_list = list(num)
        mutated = False
        
        for i in range(len(num_list)):
            digit = int(num_list[i])
            if change[digit] > digit:
                num_list[i] = str(change[digit])
                mutated = True
            elif change[digit] < digit and mutated:
                break
        
        return ''.join(num_list)