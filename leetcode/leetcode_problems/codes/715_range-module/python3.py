class RangeModule:

    def __init__(self):
        self.ranges = []

    def addRange(self, left: int, right: int) -> None:
        newRanges = []
        inserted = False
        for start, end in self.ranges:
            if end < left:
                newRanges.append((start, end))
            elif start > right:
                if not inserted:
                    newRanges.append((left, right))
                    inserted = True
                newRanges.append((start, end))
            else:
                left = min(left, start)
                right = max(right, end)
        if not inserted:
            newRanges.append((left, right))
        self.ranges = newRanges

    def queryRange(self, left: int, right: int) -> bool:
        for start, end in self.ranges:
            if start <= left and right <= end:
                return True
        return False

    def removeRange(self, left: int, right: int) -> None:
        newRanges = []
        for start, end in self.ranges:
            if end < left or start > right:
                newRanges.append((start, end))
            else:
                if start < left:
                    newRanges.append((start, left))
                if end > right:
                    newRanges.append((right, end))
        self.ranges = newRanges
