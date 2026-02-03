"""
Problem: Grumpy Bookstore Owner
Difficulty: Medium
Tags: array

Approach: Sliding window - find window of minutes where we can save most customers
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def maxSatisfied(self, customers: List[int], grumpy: List[int], minutes: int) -> int:
        base_satisfied = sum(customers[i] for i in range(len(customers)) if grumpy[i] == 0)
        
        max_extra = 0
        current_extra = 0
        
        for i in range(len(customers)):
            if grumpy[i] == 1:
                current_extra += customers[i]
            if i >= minutes and grumpy[i - minutes] == 1:
                current_extra -= customers[i - minutes]
            max_extra = max(max_extra, current_extra)
        
        return base_satisfied + max_extra