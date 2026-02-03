class Solution:
    def carFleet(self, target: int, position: List[int], speed: List[int]) -> int:
        cars = sorted(zip(position, speed))
        times = [(target - pos) / spd for pos, spd in cars]
        
        result = 0
        cur = 0
        for time in reversed(times):
            if time > cur:
                result += 1
                cur = time
        
        return result
