"""
Problem: Walking Robot Simulation II
Difficulty: Medium
Tags: array, simulation

Approach: Simulate robot movement with direction changes, use modulo for cycles
Time Complexity: O(1) per operation
Space Complexity: O(1)
"""

class Robot:

    def __init__(self, width: int, height: int):
        self.width = width
        self.height = height
        self.x = 0
        self.y = 0
        self.dir = 0  # 0: East, 1: North, 2: West, 3: South
        self.directions = [(1, 0), (0, 1), (-1, 0), (0, -1)]
        self.dir_names = ['East', 'North', 'West', 'South']
        self.perimeter = 2 * (width + height - 2)

    def step(self, num: int) -> None:
        num %= self.perimeter
        if num == 0:
            num = self.perimeter
        
        for _ in range(num):
            dx, dy = self.directions[self.dir]
            nx, ny = self.x + dx, self.y + dy
            
            if 0 <= nx < self.width and 0 <= ny < self.height:
                self.x, self.y = nx, ny
            else:
                # Turn right
                self.dir = (self.dir + 1) % 4
                dx, dy = self.directions[self.dir]
                self.x += dx
                self.y += dy

    def getPos(self) -> List[int]:
        return [self.x, self.y]

    def getDir(self) -> str:
        return self.dir_names[self.dir]