"""
Problem: Palindrome Partitioning
Difficulty: Medium
Tags: string, tree, dp

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

class Solution:
    def partition(self, s: str) -> List[List[str]]:
        result = []
        
        def isPalindrome(start, end):
            while start < end:
                if s[start] != s[end]:
                    return False
                start += 1
                end -= 1
            return True
        
        def backtrack(start, path):
            if start == len(s):
                result.append(list(path))
                return
            
            for end in range(start, len(s)):
                if isPalindrome(start, end):
                    path.append(s[start:end+1])
                    backtrack(end + 1, path)
                    path.pop()
        
        backtrack(0, [])
        return result