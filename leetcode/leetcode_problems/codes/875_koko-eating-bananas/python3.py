class Solution:
    def minEatingSpeed(self, piles: List[int], h: int) -> int:
        def canFinish(speed):
            return sum((pile + speed - 1) // speed for pile in piles) <= h
        
        left, right = 1, max(piles)
        while left < right:
            mid = (left + right) // 2
            if canFinish(mid):
                right = mid
            else:
                left = mid + 1
        return left
