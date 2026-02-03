from collections import Counter

class Solution:
    def largestOverlap(self, img1: List[List[int]], img2: List[List[int]]) -> int:
        n = len(img1)
        A = [(i, j) for i in range(n) for j in range(n) if img1[i][j]]
        B = [(i, j) for i in range(n) for j in range(n) if img2[i][j]]
        
        count = Counter((ax - bx, ay - by) for ax, ay in A for bx, by in B)
        return max(count.values() or [0])
