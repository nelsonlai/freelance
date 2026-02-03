"""
Problem: Maximum Number of Achievable Transfer Requests
Difficulty: Hard
Tags: array, backtracking, bit manipulation

Approach: Try all subsets of requests using backtracking, check if net transfer is zero for all buildings
Time Complexity: O(2^m * n) where m is number of requests, n is buildings
Space Complexity: O(n) for balance array
"""

class Solution:
    def maximumRequests(self, n: int, requests: List[List[int]]) -> int:
        m = len(requests)
        result = 0
        
        def backtrack(idx, count, balance):
            nonlocal result
            if idx == m:
                if all(b == 0 for b in balance):
                    result = max(result, count)
                return
            
            # Skip this request
            backtrack(idx + 1, count, balance)
            
            # Take this request
            from_building, to_building = requests[idx]
            balance[from_building] -= 1
            balance[to_building] += 1
            backtrack(idx + 1, count + 1, balance)
            balance[from_building] += 1
            balance[to_building] -= 1
        
        backtrack(0, 0, [0] * n)
        return result