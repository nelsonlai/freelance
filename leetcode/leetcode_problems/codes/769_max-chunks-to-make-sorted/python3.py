class Solution:
    def maxChunksToSorted(self, arr: List[int]) -> int:
        result = 0
        maxVal = 0
        for i, num in enumerate(arr):
            maxVal = max(maxVal, num)
            if maxVal == i:
                result += 1
        return result
