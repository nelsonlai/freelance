"""
Problem: Smallest K-Length Subsequence With Occurrences of a Letter
Difficulty: Hard
Tags: string, graph, greedy, stack

Approach: Greedy with stack - maintain smallest lexicographic subsequence while ensuring letter count
Time Complexity: O(n) where n is length
Space Complexity: O(n)
"""

class Solution:
    def smallestSubsequence(self, s: str, k: int, letter: str, repetition: int) -> str:
        n = len(s)
        # Count remaining occurrences of letter after each position
        letter_count = [0] * n
        count = 0
        for i in range(n - 1, -1, -1):
            if s[i] == letter:
                count += 1
            letter_count[i] = count
        
        stack = []
        letter_used = 0  # Count of letter used in stack
        
        for i, char in enumerate(s):
            # Pop if we can maintain k-length and letter requirement
            while stack and stack[-1] > char:
                # Check if we can still form valid subsequence after popping
                remaining_chars = n - i
                remaining_letters = letter_count[i]
                stack_size = len(stack)
                
                # After popping, we need: (k - stack_size) chars and (repetition - letter_used) letters
                if stack_size + remaining_chars >= k and letter_used + remaining_letters >= repetition:
                    popped = stack.pop()
                    if popped == letter:
                        letter_used -= 1
                else:
                    break
            
            # Add current character if we have space
            if len(stack) < k:
                stack.append(char)
                if char == letter:
                    letter_used += 1
            else:
                # Replace if current is smaller and we can maintain requirements
                if stack and stack[-1] > char:
                    popped = stack.pop()
                    if popped == letter:
                        letter_used -= 1
                    stack.append(char)
                    if char == letter:
                        letter_used += 1
        
        return ''.join(stack)