class Solution:
    def lenLongestFibSubseq(self, arr: List[int]) -> int:
        index = {x: i for i, x in enumerate(arr)}
        longest = {}
        result = 0
        
        for k in range(len(arr)):
            for j in range(k):
                i = index.get(arr[k] - arr[j], -1)
                if i >= 0 and i < j:
                    cand = longest.get((i, j), 2) + 1
                    longest[(j, k)] = cand
                    result = max(result, cand)
        
        return result if result >= 3 else 0
