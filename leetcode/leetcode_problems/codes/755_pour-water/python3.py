class Solution:
    def pourWater(self, heights: List[int], volume: int, k: int) -> List[int]:
        for _ in range(volume):
            pos = k
            
            # Try to move left
            while pos > 0 and heights[pos] >= heights[pos - 1]:
                pos -= 1
            
            # Try to move right if can't move left
            if pos == k:
                while pos < len(heights) - 1 and heights[pos] >= heights[pos + 1]:
                    pos += 1
                while pos > k and heights[pos] == heights[pos - 1]:
                    pos -= 1
            
            heights[pos] += 1
        
        return heights
