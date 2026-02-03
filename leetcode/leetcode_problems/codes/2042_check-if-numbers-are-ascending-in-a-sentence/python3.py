"""
Problem: Check if Numbers Are Ascending in a Sentence
Difficulty: Easy
Tags: string

Approach: Extract all numbers, check if they form strictly increasing sequence
Time Complexity: O(n) where n is length
Space Complexity: O(k) where k is number of numbers
"""

class Solution:
    def areNumbersAscending(self, s: str) -> bool:
        words = s.split()
        numbers = []
        
        for word in words:
            if word.isdigit():
                numbers.append(int(word))
        
        for i in range(1, len(numbers)):
            if numbers[i] <= numbers[i - 1]:
                return False
        
        return True