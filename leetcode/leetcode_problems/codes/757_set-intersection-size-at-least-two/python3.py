class Solution:
    def intersectionSizeTwo(self, intervals: List[List[int]]) -> int:
        intervals.sort(key=lambda x: (x[1], -x[0]))
        result = []
        
        for start, end in intervals:
            count = sum(1 for x in result if start <= x <= end)
            if count == 0:
                result.extend([end - 1, end])
            elif count == 1:
                result.append(end)
        
        return len(result)
