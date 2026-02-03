class Solution:
    def fairCandySwap(self, aliceSizes: List[int], bobSizes: List[int]) -> List[int]:
        sumA, sumB = sum(aliceSizes), sum(bobSizes)
        diff = (sumB - sumA) // 2
        setB = set(bobSizes)
        
        for a in aliceSizes:
            if a + diff in setB:
                return [a, a + diff]
        
        return []
