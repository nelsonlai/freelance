"""
Problem: Circular Array Loop
Difficulty: Medium
Tags: array, graph, hash

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) for hash map
"""

class Solution:
    def circularArrayLoop(self, nums: List[int]) -> bool:
        n = len(nums)
        
        def get_next(i):
            return (i + nums[i]) % n
        
        for i in range(n):
            if nums[i] == 0:
                continue
            
            slow = fast = i
            direction = nums[i] > 0
            
            while True:
                slow = get_next(slow)
                fast = get_next(get_next(fast))
                
                if (nums[slow] > 0) != direction or (nums[fast] > 0) != direction:
                    break
                
                if slow == fast:
                    if slow == get_next(slow):
                        break
                    return True
            
            visited = i
            while (nums[visited] > 0) == direction:
                next_idx = get_next(visited)
                nums[visited] = 0
                visited = next_idx
        
        return False