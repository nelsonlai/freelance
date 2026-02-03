"""
Problem: Design Underground System
Difficulty: Medium
Tags: string, hash

Approach: Track check-ins, store trip times, calculate averages
Time Complexity: O(1) for all operations
Space Complexity: O(n) for check-ins and trips
"""

from collections import defaultdict

class UndergroundSystem:

    def __init__(self):
        self.check_ins = {}
        self.trips = defaultdict(list)

    def checkIn(self, id: int, stationName: str, t: int) -> None:
        self.check_ins[id] = (stationName, t)

    def checkOut(self, id: int, stationName: str, t: int) -> None:
        start_station, start_time = self.check_ins.pop(id)
        self.trips[(start_station, stationName)].append(t - start_time)

    def getAverageTime(self, startStation: str, endStation: str) -> float:
        times = self.trips[(startStation, endStation)]
        return sum(times) / len(times)