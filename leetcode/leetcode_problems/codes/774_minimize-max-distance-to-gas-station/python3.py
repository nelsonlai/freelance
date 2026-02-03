class Solution:
    def minmaxGasDist(self, stations: List[int], k: int) -> float:
        def possible(D):
            return sum(int((stations[i+1] - stations[i]) / D) for i in range(len(stations) - 1)) <= k
        
        left, right = 0, stations[-1] - stations[0]
        while right - left > 1e-6:
            mid = (left + right) / 2.0
            if possible(mid):
                right = mid
            else:
                left = mid
        return left
