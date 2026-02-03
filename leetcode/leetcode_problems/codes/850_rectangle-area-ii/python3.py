class Solution:
    def rectangleArea(self, rectangles: List[List[int]]) -> int:
        MOD = 10**9 + 7
        events = []
        for x1, y1, x2, y2 in rectangles:
            events.append((y1, 1, x1, x2))
            events.append((y2, -1, x1, x2))
        events.sort()
        
        def query():
            result = 0
            cur = -1
            for x1, x2 in active:
                cur = max(cur, x1)
                result += max(0, x2 - cur)
                cur = max(cur, x2)
            return result
        
        active = []
        curY = events[0][0]
        result = 0
        
        for y, typ, x1, x2 in events:
            result += query() * (y - curY)
            curY = y
            
            if typ == 1:
                active.append((x1, x2))
                active.sort()
            else:
                active.remove((x1, x2))
        
        return result % MOD
