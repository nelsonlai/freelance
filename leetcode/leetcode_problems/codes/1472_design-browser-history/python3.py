"""
Problem: Design Browser History
Difficulty: Medium
Tags: array, string, linked_list, stack

Approach: Use list to store history, track current position and end
Time Complexity: O(1) for all operations
Space Complexity: O(n) for history
"""

class BrowserHistory:

    def __init__(self, homepage: str):
        self.history = [homepage]
        self.current = 0
        self.end = 0

    def visit(self, url: str) -> None:
        self.current += 1
        if self.current < len(self.history):
            self.history[self.current] = url
        else:
            self.history.append(url)
        self.end = self.current

    def back(self, steps: int) -> str:
        self.current = max(0, self.current - steps)
        return self.history[self.current]

    def forward(self, steps: int) -> str:
        self.current = min(self.end, self.current + steps)
        return self.history[self.current]