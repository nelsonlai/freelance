"""
Problem: String Without AAA or BBB
Difficulty: Medium
Tags: string, tree, greedy

Approach: Greedy - always append the character with more remaining, avoid 3 consecutive
Time Complexity: O(a + b)
Space Complexity: O(a + b) for result
"""

class Solution:
    def strWithout3a3b(self, a: int, b: int) -> str:
        result = []
        i, j = 0, 0
        
        while a > 0 or b > 0:
            write_a = False
            if len(result) >= 2 and result[-1] == result[-2]:
                if result[-1] == 'b':
                    write_a = True
            else:
                if a >= b:
                    write_a = True
            
            if write_a:
                result.append('a')
                a -= 1
            else:
                result.append('b')
                b -= 1
        
        return ''.join(result)