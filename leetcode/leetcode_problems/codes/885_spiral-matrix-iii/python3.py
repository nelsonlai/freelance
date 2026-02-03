class Solution:
    def spiralMatrixIII(self, rows: int, cols: int, rStart: int, cStart: int) -> List[List[int]]:
        result = []
        r, c = rStart, cStart
        dr, dc = 0, 1
        step = 1
        
        while len(result) < rows * cols:
            for _ in range(2):
                for _ in range(step):
                    if 0 <= r < rows and 0 <= c < cols:
                        result.append([r, c])
                    r += dr
                    c += dc
                dr, dc = dc, -dr
            step += 1
        
        return result
