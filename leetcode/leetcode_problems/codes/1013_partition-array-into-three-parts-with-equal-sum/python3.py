"""
Problem: Partition Array Into Three Parts With Equal Sum
Difficulty: Easy
Tags: array, greedy

Approach: Check if sum is divisible by 3, then find two split points
Time Complexity: O(n)
Space Complexity: O(1)
"""

class Solution:
    def canThreePartsEqualSum(self, arr: List[int]) -> bool:
        total = sum(arr)
        if total % 3 != 0:
            return False
        
        target = total // 3
        current_sum = 0
        count = 0
        
        for num in arr:
            current_sum += num
            if current_sum == target:
                count += 1
                current_sum = 0
                if count == 2:
                    return True
        
        return False