"""
Problem: Find Minimum Time to Finish All Jobs
Difficulty: Hard
Tags: array, dp, backtracking, binary search

Approach: Binary search on answer, use backtracking to check if jobs can be assigned within limit
Time Complexity: O(k^n * log(sum)) where n is jobs
Space Complexity: O(k)
"""

class Solution:
    def minimumTimeRequired(self, jobs: List[int], k: int) -> int:
        jobs.sort(reverse=True)
        
        def canAssign(limit):
            workers = [0] * k
            
            def backtrack(idx):
                if idx == len(jobs):
                    return True
                
                for i in range(k):
                    if workers[i] + jobs[idx] <= limit:
                        workers[i] += jobs[idx]
                        if backtrack(idx + 1):
                            return True
                        workers[i] -= jobs[idx]
                    
                    if workers[i] == 0:
                        break
                
                return False
            
            return backtrack(0)
        
        left, right = max(jobs), sum(jobs)
        
        while left < right:
            mid = (left + right) // 2
            if canAssign(mid):
                right = mid
            else:
                left = mid + 1
        
        return left