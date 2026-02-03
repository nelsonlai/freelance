class Solution:
    def maxDistToClosest(self, seats: List[int]) -> int:
        n = len(seats)
        result = 0
        last = -1
        
        for i in range(n):
            if seats[i] == 1:
                if last == -1:
                    result = i
                else:
                    result = max(result, (i - last) // 2)
                last = i
        
        result = max(result, n - 1 - last)
        return result
