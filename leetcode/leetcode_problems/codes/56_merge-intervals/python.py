class Solution(object):
    def merge(self, intervals):
        """
        :type intervals: List[List[int]]
        :rtype: List[List[int]]
        """
        if not intervals:
            return []
        
        intervals.sort(key=lambda x: x[0])
        result = [intervals[0]]
        
        for current in intervals[1:]:
            if current[0] <= result[-1][1]:
                result[-1][1] = max(result[-1][1], current[1])
            else:
                result.append(current)
        
        return result