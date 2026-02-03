class Solution:
    def largestTriangleArea(self, points: List[List[int]]) -> float:
        def area(p1, p2, p3):
            return abs(p1[0]*(p2[1]-p3[1]) + p2[0]*(p3[1]-p1[1]) + p3[0]*(p1[1]-p2[1])) / 2.0
        
        maxArea = 0
        n = len(points)
        for i in range(n):
            for j in range(i+1, n):
                for k in range(j+1, n):
                    maxArea = max(maxArea, area(points[i], points[j], points[k]))
        return maxArea
