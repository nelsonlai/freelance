"""
Problem: Design File System
Difficulty: Medium
Tags: string, hash

Approach: Use hash map to store paths, validate parent path exists
Time Complexity: O(n) for createPath where n is path length, O(1) for get
Space Complexity: O(n) for storing all paths
"""

class FileSystem:

    def __init__(self):
        self.paths = {}

    def createPath(self, path: str, value: int) -> bool:
        if path in self.paths:
            return False
        
        if path == "/":
            self.paths[path] = value
            return True
        
        # Check if parent path exists
        parent = path.rsplit('/', 1)[0] or '/'
        if parent not in self.paths:
            return False
        
        self.paths[path] = value
        return True

    def get(self, path: str) -> int:
        return self.paths.get(path, -1)