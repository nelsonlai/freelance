"""
Problem: Interval List Intersections
Difficulty: Medium
Tags: array, sort

Approach: Two pointers - merge intervals from both lists, find intersections
Time Complexity: O(n + m) where n and m are list lengths
Space Complexity: O(1) excluding output
"""

class Solution:
    def intervalIntersection(self, firstList: List[List[int]], secondList: List[List[int]]) -> List[List[int]]:
        result = []
        i = j = 0
        
        while i < len(firstList) and j < len(secondList):
            start = max(firstList[i][0], secondList[j][0])
            end = min(firstList[i][1], secondList[j][1])
            
            if start <= end:
                result.append([start, end])
            
            if firstList[i][1] < secondList[j][1]:
                i += 1
            else:
                j += 1
        
        return result