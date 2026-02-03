"""
Problem: Design In-Memory File System
Difficulty: Hard
Tags: string, graph, hash, sort

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

from collections import defaultdict

class FileSystem:
    def __init__(self):
        self.files = {}
        self.dirs = defaultdict(set)

    def ls(self, path: str) -> List[str]:
        if path in self.files:
            return [path.split('/')[-1]]
        return sorted(list(self.dirs[path]))

    def mkdir(self, path: str) -> None:
        parts = path.split('/')
        for i in range(1, len(parts)):
            curr = '/'.join(parts[:i+1])
            if i < len(parts) - 1:
                self.dirs['/'.join(parts[:i])].add(parts[i])
            else:
                self.dirs['/'.join(parts[:i])].add(parts[i])

    def addContentToFile(self, filePath: str, content: str) -> None:
        if filePath not in self.files:
            self.mkdir('/'.join(filePath.split('/')[:-1]))
            self.dirs['/'.join(filePath.split('/')[:-1])].add(filePath.split('/')[-1])
        self.files[filePath] = self.files.get(filePath, '') + content

    def readContentFromFile(self, filePath: str) -> str:
        return self.files[filePath]