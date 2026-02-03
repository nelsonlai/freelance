"""
Problem: Strong Password Checker
Difficulty: Hard
Tags: string, greedy, queue, heap

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(1) to O(n) depending on approach
"""

class Solution:
    def strongPasswordChecker(self, password: str) -> int:
        n = len(password)
        missing_types = 3
        has_lower = has_upper = has_digit = False
        
        for char in password:
            if char.islower():
                has_lower = True
            elif char.isupper():
                has_upper = True
            elif char.isdigit():
                has_digit = True
        
        if has_lower:
            missing_types -= 1
        if has_upper:
            missing_types -= 1
        if has_digit:
            missing_types -= 1
        
        replace = 0
        one = two = 0
        
        i = 0
        while i < n:
            length = 1
            while i + length < n and password[i + length] == password[i]:
                length += 1
            
            if length >= 3:
                replace += length // 3
                if length % 3 == 0:
                    one += 1
                elif length % 3 == 1:
                    two += 1
            
            i += length
        
        if n < 6:
            return max(missing_types, 6 - n)
        elif n <= 20:
            return max(missing_types, replace)
        else:
            delete = n - 20
            replace -= min(delete, one)
            replace -= min(max(delete - one, 0), two * 2) // 2
            replace -= max(delete - one - 2 * two, 0) // 3
            return delete + max(missing_types, replace)