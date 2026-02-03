class Solution:
    def robotSim(self, commands: List[int], obstacles: List[List[int]]) -> int:
        obstacles_set = {tuple(ob) for ob in obstacles}
        x = y = 0
        dx, dy = 0, 1
        result = 0
        
        for cmd in commands:
            if cmd == -2:
                dx, dy = -dy, dx
            elif cmd == -1:
                dx, dy = dy, -dx
            else:
                for _ in range(cmd):
                    if (x + dx, y + dy) not in obstacles_set:
                        x += dx
                        y += dy
                        result = max(result, x*x + y*y)
                    else:
                        break
        
        return result
