class MyCalendarTwo:

    def __init__(self):
        self.events = []
        self.overlaps = []

    def book(self, startTime: int, endTime: int) -> bool:
        for start, end in self.overlaps:
            if start < endTime and startTime < end:
                return False
        
        for start, end in self.events:
            if start < endTime and startTime < end:
                self.overlaps.append((max(start, startTime), min(end, endTime)))
        
        self.events.append((startTime, endTime))
        return True
