"""
Problem: Design Log Storage System
Difficulty: Medium
Tags: string, hash

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class LogSystem:
    def __init__(self):
        self.logs = []
        self.granularity_map = {
            "Year": 4,
            "Month": 7,
            "Day": 10,
            "Hour": 13,
            "Minute": 16,
            "Second": 19
        }

    def put(self, id: int, timestamp: str) -> None:
        self.logs.append((id, timestamp))

    def retrieve(self, start: str, end: str, granularity: str) -> List[int]:
        idx = self.granularity_map[granularity]
        start_prefix = start[:idx]
        end_prefix = end[:idx]
        
        result = []
        for log_id, timestamp in self.logs:
            prefix = timestamp[:idx]
            if start_prefix <= prefix <= end_prefix:
                result.append(log_id)
        
        return result