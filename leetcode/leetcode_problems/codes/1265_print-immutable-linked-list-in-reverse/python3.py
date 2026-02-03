"""
Problem: Print Immutable Linked List in Reverse
Difficulty: Medium
Tags: array, linked_list, stack

Approach: Recursion to traverse to end, then print on way back
Time Complexity: O(n) where n is number of nodes
Space Complexity: O(n) for recursion stack
"""

# """
# This is the ImmutableListNode's API interface.
# You should not implement it, or speculate about its implementation.
# """
# class ImmutableListNode:
#     def printValue(self) -> None: # print the value of this node.
#     def getNext(self) -> 'ImmutableListNode': # return the next node.

class Solution:
    def printLinkedListInReverse(self, head: 'ImmutableListNode') -> None:
        if head is None:
            return
        self.printLinkedListInReverse(head.getNext())
        head.printValue()