class MyCalendar:

    def __init__(self):
        self.events = []

    def book(self, startTime: int, endTime: int) -> bool:
        for start, end in self.events:
            if start < endTime and startTime < end:
                return False
        self.events.append((startTime, endTime))
        return True
