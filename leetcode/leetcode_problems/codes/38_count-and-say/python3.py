"""
Problem: Count and Say
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def countAndSay(self, n: int) -> str:
        if n == 1:
            return "1"
        
        result = "1"
        for _ in range(n - 1):
            new_result = []
            i = 0
            while i < len(result):
                count = 1
                while i + 1 < len(result) and result[i] == result[i + 1]:
                    count += 1
                    i += 1
                new_result.append(str(count))
                new_result.append(result[i])
                i += 1
            result = ''.join(new_result)
        
        return result