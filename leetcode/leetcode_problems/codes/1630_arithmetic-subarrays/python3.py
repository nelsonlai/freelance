"""
Problem: Arithmetic Subarrays
Difficulty: Medium
Tags: array, hash, sort

Approach: For each query, extract subarray, sort, check if differences are equal
Time Complexity: O(m * n log n) where m is queries, n is subarray length
Space Complexity: O(n) for subarray
"""

class Solution:
    def checkArithmeticSubarrays(self, nums: List[int], l: List[int], r: List[int]) -> List[bool]:
        result = []
        
        for left, right in zip(l, r):
            subarray = sorted(nums[left:right+1])
            if len(subarray) < 2:
                result.append(True)
                continue
            
            diff = subarray[1] - subarray[0]
            is_arithmetic = True
            for i in range(2, len(subarray)):
                if subarray[i] - subarray[i-1] != diff:
                    is_arithmetic = False
                    break
            
            result.append(is_arithmetic)
        
        return result