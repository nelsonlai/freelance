from sortedcontainers import SortedDict

class MyCalendarThree:

    def __init__(self):
        self.delta = SortedDict()

    def book(self, startTime: int, endTime: int) -> int:
        self.delta[startTime] = self.delta.get(startTime, 0) + 1
        self.delta[endTime] = self.delta.get(endTime, 0) - 1
        
        active = 0
        maxActive = 0
        for count in self.delta.values():
            active += count
            maxActive = max(maxActive, active)
        
        return maxActive
