from collections import Counter
import heapq

class Solution:
    def reorganizeString(self, s: str) -> str:
        count = Counter(s)
        heap = [(-freq, char) for char, freq in count.items()]
        heapq.heapify(heap)
        
        result = []
        prev = None
        
        while heap or prev:
            if not heap and prev:
                return ""
            
            freq, char = heapq.heappop(heap)
            result.append(char)
            freq += 1
            
            if prev:
                heapq.heappush(heap, prev)
                prev = None
            
            if freq < 0:
                prev = (freq, char)
        
        return ''.join(result)
