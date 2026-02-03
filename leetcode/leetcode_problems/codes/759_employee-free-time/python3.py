import heapq

class Solution:
    def employeeFreeTime(self, schedule: '[[Interval]]') -> '[Interval]':
        intervals = []
        for emp in schedule:
            intervals.extend(emp)
        
        intervals.sort(key=lambda x: x.start)
        merged = []
        
        for interval in intervals:
            if not merged or merged[-1].end < interval.start:
                merged.append(interval)
            else:
                merged[-1].end = max(merged[-1].end, interval.end)
        
        result = []
        for i in range(len(merged) - 1):
            result.append(Interval(merged[i].end, merged[i + 1].start))
        
        return result
