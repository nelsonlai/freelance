"""
Problem: Find Array Given Subset Sums
Difficulty: Hard
Tags: array, recursion, subset sum

Approach: Recursively recover array from subset sums
Time Complexity: O(n * 2^n) where n is array length
Space Complexity: O(2^n)
"""

from collections import Counter

class Solution:
    def recoverArray(self, n: int, sums: List[int]) -> List[int]:
        sums.sort()
        result = []
        
        def recover(sums_list, target):
            if len(sums_list) == 1:
                return []
            
            # Find the smallest non-zero element
            diff = sums_list[1] - sums_list[0]
            
            # Split into two groups: with and without diff
            counter = Counter(sums_list)
            with_diff = []
            without_diff = []
            
            for s in sums_list:
                if counter[s] > 0:
                    without_diff.append(s)
                    counter[s] -= 1
                    if counter[s + diff] > 0:
                        with_diff.append(s + diff)
                        counter[s + diff] -= 1
            
            # Try both possibilities
            if diff in without_diff:
                res = recover(without_diff, diff)
                if res is not None:
                    return [diff] + res
            
            # Try negative
            if -diff in with_diff:
                res = recover(without_diff, -diff)
                if res is not None:
                    return [-diff] + res
            
            return None
        
        return recover(sums, 0)