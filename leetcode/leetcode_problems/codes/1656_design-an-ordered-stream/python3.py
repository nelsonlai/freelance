"""
Problem: Design an Ordered Stream
Difficulty: Easy
Tags: array, string, hash, design

Approach: Store values in array, return consecutive values starting from pointer
Time Complexity: O(k) for insert where k is consecutive values
Space Complexity: O(n) for storage
"""

class OrderedStream:

    def __init__(self, n: int):
        self.stream = [None] * (n + 1)
        self.ptr = 1

    def insert(self, idKey: int, value: str) -> List[str]:
        self.stream[idKey] = value
        result = []
        
        while self.ptr < len(self.stream) and self.stream[self.ptr] is not None:
            result.append(self.stream[self.ptr])
            self.ptr += 1
        
        return result