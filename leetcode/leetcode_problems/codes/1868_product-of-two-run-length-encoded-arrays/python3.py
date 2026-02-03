"""
Problem: Product of Two Run-Length Encoded Arrays
Difficulty: Medium
Tags: array, two pointers

Approach: Two pointers to process both encoded arrays, merge consecutive same values
Time Complexity: O(n + m) where n, m are encoded lengths
Space Complexity: O(1) excluding output
"""

class Solution:
    def findRLEArray(self, encoded1: List[List[int]], encoded2: List[List[int]]) -> List[List[int]]:
        i = j = 0
        result = []
        
        while i < len(encoded1) and j < len(encoded2):
            val1, count1 = encoded1[i]
            val2, count2 = encoded2[j]
            
            product = val1 * val2
            min_count = min(count1, count2)
            
            # Merge with previous if same value
            if result and result[-1][0] == product:
                result[-1][1] += min_count
            else:
                result.append([product, min_count])
            
            encoded1[i][1] -= min_count
            encoded2[j][1] -= min_count
            
            if encoded1[i][1] == 0:
                i += 1
            if encoded2[j][1] == 0:
                j += 1
        
        return result