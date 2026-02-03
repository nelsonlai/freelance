from collections import defaultdict
import bisect

class TopVotedCandidate:
    def __init__(self, persons: List[int], times: List[int]):
        self.times = times
        self.leaders = []
        count = defaultdict(int)
        leader = -1
        
        for person, time in zip(persons, times):
            count[person] += 1
            if count[person] >= count.get(leader, 0):
                leader = person
            self.leaders.append(leader)
    
    def q(self, t: int) -> int:
        idx = bisect.bisect_right(self.times, t) - 1
        return self.leaders[idx]
