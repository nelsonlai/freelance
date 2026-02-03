class Solution:
    def maxProfitAssignment(self, difficulty: List[int], profit: List[int], worker: List[int]) -> int:
        jobs = sorted(zip(difficulty, profit))
        worker.sort()
        
        result = 0
        i = 0
        best = 0
        
        for ability in worker:
            while i < len(jobs) and jobs[i][0] <= ability:
                best = max(best, jobs[i][1])
                i += 1
            result += best
        
        return result
