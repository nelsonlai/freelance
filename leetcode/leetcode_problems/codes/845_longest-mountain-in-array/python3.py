class Solution:
    def longestMountain(self, arr: List[int]) -> int:
        n = len(arr)
        result = 0
        i = 1
        
        while i < n:
            while i < n and arr[i-1] >= arr[i]:
                i += 1
            start = i - 1
            
            while i < n and arr[i-1] < arr[i]:
                i += 1
            peak = i - 1
            
            while i < n and arr[i-1] > arr[i]:
                i += 1
            end = i - 1
            
            if peak > start and end > peak:
                result = max(result, end - start + 1)
        
        return result
