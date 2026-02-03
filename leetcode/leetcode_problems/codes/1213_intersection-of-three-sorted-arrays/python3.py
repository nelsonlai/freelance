"""
Problem: Intersection of Three Sorted Arrays
Difficulty: Easy
Tags: array, hash, sort, search

Approach: Three pointers - move pointer with smallest value
Time Complexity: O(n) where n is total length of arrays
Space Complexity: O(1) excluding result
"""

class Solution:
    def arraysIntersection(self, arr1: List[int], arr2: List[int], arr3: List[int]) -> List[int]:
        i = j = k = 0
        result = []
        
        while i < len(arr1) and j < len(arr2) and k < len(arr3):
            if arr1[i] == arr2[j] == arr3[k]:
                result.append(arr1[i])
                i += 1
                j += 1
                k += 1
            elif arr1[i] < arr2[j]:
                i += 1
            elif arr2[j] < arr3[k]:
                j += 1
            else:
                k += 1
        
        return result