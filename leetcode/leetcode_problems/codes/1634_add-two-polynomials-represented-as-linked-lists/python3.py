"""
Problem: Add Two Polynomials Represented as Linked Lists
Difficulty: Medium
Tags: array, math, linked_list, two pointers

Approach: Merge two sorted linked lists by power, combine coefficients for same power
Time Complexity: O(n + m) where n, m are lengths
Space Complexity: O(1)
"""

# Definition for polynomial singly-linked list.
# class PolyNode:
#     def __init__(self, x=0, y=0, next=None):
#         self.coefficient = x
#         self.power = y
#         self.next = next

class Solution:
    def addPoly(self, poly1: 'PolyNode', poly2: 'PolyNode') -> 'PolyNode':
        dummy = PolyNode()
        current = dummy
        
        while poly1 and poly2:
            if poly1.power > poly2.power:
                current.next = PolyNode(poly1.coefficient, poly1.power)
                poly1 = poly1.next
                current = current.next
            elif poly2.power > poly1.power:
                current.next = PolyNode(poly2.coefficient, poly2.power)
                poly2 = poly2.next
                current = current.next
            else:
                coeff = poly1.coefficient + poly2.coefficient
                if coeff != 0:
                    current.next = PolyNode(coeff, poly1.power)
                    current = current.next
                poly1 = poly1.next
                poly2 = poly2.next
        
        current.next = poly1 or poly2
        
        return dummy.next