"""
Problem: Find the Minimum and Maximum Number of Nodes Between Critical Points
Difficulty: Medium
Tags: array, linked_list

Approach: Traverse linked list, find critical points, calculate min and max distances
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(1)
"""

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        if not head or not head.next or not head.next.next:
            return [-1, -1]
        
        critical_points = []
        prev = head
        curr = head.next
        index = 1
        
        while curr.next:
            # Check if current is a critical point
            if (prev.val < curr.val > curr.next.val) or (prev.val > curr.val < curr.next.val):
                critical_points.append(index)
            
            prev = curr
            curr = curr.next
            index += 1
        
        if len(critical_points) < 2:
            return [-1, -1]
        
        # Minimum distance is between consecutive critical points
        min_dist = float('inf')
        for i in range(1, len(critical_points)):
            min_dist = min(min_dist, critical_points[i] - critical_points[i - 1])
        
        # Maximum distance is between first and last
        max_dist = critical_points[-1] - critical_points[0]
        
        return [min_dist, max_dist]