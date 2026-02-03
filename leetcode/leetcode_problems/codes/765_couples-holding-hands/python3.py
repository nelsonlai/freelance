class Solution:
    def minSwapsCouples(self, row: List[int]) -> int:
        n = len(row)
        pos = {row[i]: i for i in range(n)}
        swaps = 0
        
        for i in range(0, n, 2):
            partner = row[i] ^ 1
            if row[i + 1] != partner:
                j = pos[partner]
                row[i + 1], row[j] = row[j], row[i + 1]
                pos[row[i + 1]] = i + 1
                pos[row[j]] = j
                swaps += 1
        
        return swaps
