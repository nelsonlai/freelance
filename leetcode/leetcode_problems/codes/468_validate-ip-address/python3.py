"""
Problem: Validate IP Address
Difficulty: Medium
Tags: string

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def validIPAddress(self, queryIP: str) -> str:
        def isIPv4(s):
            parts = s.split('.')
            if len(parts) != 4:
                return False
            for part in parts:
                if not part or (len(part) > 1 and part[0] == '0'):
                    return False
                try:
                    num = int(part)
                    if num < 0 or num > 255:
                        return False
                except:
                    return False
            return True
        
        def isIPv6(s):
            parts = s.split(':')
            if len(parts) != 8:
                return False
            for part in parts:
                if not part or len(part) > 4:
                    return False
                for char in part:
                    if char not in '0123456789abcdefABCDEF':
                        return False
            return True
        
        if '.' in queryIP:
            return "IPv4" if isIPv4(queryIP) else "Neither"
        elif ':' in queryIP:
            return "IPv6" if isIPv6(queryIP) else "Neither"
        return "Neither"