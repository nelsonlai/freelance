"""
Problem: Delivering Boxes from Storage to Ports
Difficulty: Hard
Tags: array, dp, sliding window, monotonic queue

Approach: DP - dp[i] = min trips to deliver first i boxes, use sliding window for optimization
Time Complexity: O(n) where n is number of boxes
Space Complexity: O(n)
"""

from collections import deque

class Solution:
    def boxDelivering(self, boxes: List[List[int]], portsCount: int, maxBoxes: int, maxWeight: int) -> int:
        n = len(boxes)
        dp = [0] * (n + 1)
        dq = deque([0])
        
        weight = 0
        j = 0
        
        for i in range(n):
            weight += boxes[i][1]
            
            while weight > maxWeight or i - j + 1 > maxBoxes:
                weight -= boxes[j][1]
                j += 1
            
            while dq and dq[0] < j:
                dq.popleft()
            
            trips = 2
            for k in range(j, i):
                if boxes[k][0] != boxes[k + 1][0]:
                    trips += 1
            
            dp[i + 1] = dp[dq[0]] + trips
            
            if i < n - 1:
                cost = dp[i + 1] - (1 if boxes[i][0] != boxes[i + 1][0] else 0)
                while dq and dp[dq[-1]] >= cost:
                    dq.pop()
                dq.append(i + 1)
        
        return dp[n]