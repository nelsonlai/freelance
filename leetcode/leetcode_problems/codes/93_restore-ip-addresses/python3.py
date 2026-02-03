"""
Problem: Restore IP Addresses
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def restoreIpAddresses(self, s: str) -> List[str]:
        result = []
        
        def backtrack(start, path):
            if len(path) == 4:
                if start == len(s):
                    result.append('.'.join(path))
                return
            
            for i in range(start, min(start + 3, len(s))):
                segment = s[start:i + 1]
                if (segment[0] == '0' and len(segment) > 1) or int(segment) > 255:
                    continue
                path.append(segment)
                backtrack(i + 1, path)
                path.pop()
        
        backtrack(0, [])
        return result