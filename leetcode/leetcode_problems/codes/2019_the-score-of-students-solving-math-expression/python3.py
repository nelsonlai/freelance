"""
Problem: The Score of Students Solving Math Expression
Difficulty: Hard
Tags: array, string, dp, math, hash, stack

Approach: DP to compute all possible results, then score based on correct/incorrect
Time Complexity: O(n^3) where n is length of expression
Space Complexity: O(n^2)
"""

from functools import lru_cache

class Solution:
    def scoreOfStudents(self, s: str, answers: List[int]) -> int:
        # Calculate correct answer
        correct = self.evaluate(s)
        
        # Use DP to find all possible results
        @lru_cache(None)
        def dp(i, j):
            if i == j:
                return {int(s[i])}
            
            results = set()
            for k in range(i + 1, j, 2):  # Operators are at odd indices
                left = dp(i, k - 1)
                right = dp(k + 1, j)
                op = s[k]
                
                for l in left:
                    for r in right:
                        if op == '+':
                            val = l + r
                        else:  # op == '*'
                            val = l * r
                        if val <= 1000:  # Constraint: answers <= 1000
                            results.add(val)
            
            return results
        
        all_results = dp(0, len(s) - 1)
        
        # Score answers
        score = 0
        for ans in answers:
            if ans == correct:
                score += 5
            elif ans in all_results:
                score += 2
        
        return score
    
    def evaluate(self, s: str) -> int:
        """Evaluate expression correctly (multiplication before addition)"""
        stack = []
        num = 0
        op = '+'
        
        for i, char in enumerate(s):
            if char.isdigit():
                num = num * 10 + int(char)
            
            if char in '+-*' or i == len(s) - 1:
                if op == '+':
                    stack.append(num)
                elif op == '*':
                    stack.append(stack.pop() * num)
                op = char
                num = 0
        
        return sum(stack)