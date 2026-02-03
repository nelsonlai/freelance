"""
Problem: Design Snake Game
Difficulty: Medium
Tags: array, string, hash, queue

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import deque

class SnakeGame:

    def __init__(self, width: int, height: int, food: List[List[int]]):
        self.width = width
        self.height = height
        self.food = deque(food)
        self.snake = deque([(0, 0)])
        self.directions = {'U': (-1, 0), 'D': (1, 0), 'L': (0, -1), 'R': (0, 1)}
        self.score = 0

    def move(self, direction: str) -> int:
        dx, dy = self.directions[direction]
        head = self.snake[0]
        new_head = (head[0] + dx, head[1] + dy)
        
        if new_head[0] < 0 or new_head[0] >= self.height or \
           new_head[1] < 0 or new_head[1] >= self.width:
            return -1
        
        if self.food and list(new_head) == self.food[0]:
            self.food.popleft()
            self.score += 1
        else:
            self.snake.pop()
        
        if new_head in self.snake:
            return -1
        
        self.snake.appendleft(new_head)
        return self.score