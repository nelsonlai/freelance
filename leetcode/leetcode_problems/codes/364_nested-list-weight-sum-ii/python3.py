"""
Problem: Nested List Weight Sum II
Difficulty: Medium
Tags: search, stack

Approach: Optimized algorithm based on problem constraints
Time Complexity: O(n) to O(n^2) depending on approach
Space Complexity: O(1) to O(n) depending on approach
"""

# """
# This is the interface that allows for creating nested lists.
# You should not implement it, or speculate about its implementation
# """
#class NestedInteger:
#    def __init__(self, value=None):
#        """
#        If value is not specified, initializes an empty list.
#        Otherwise initializes a single integer equal to value.
#        """
#
#    def isInteger(self):
#        """
#        @return True if this NestedInteger holds a single integer, rather than a nested list.
#        :rtype bool
#        """
#
#    def add(self, elem):
#        """
#        Set this NestedInteger to hold a nested list and adds a nested integer elem to it.
#        :rtype void
#        """
#
#    def setInteger(self, value):
#        """
#        Set this NestedInteger to hold a single integer equal to value.
#        :rtype void
#        """
#
#    def getInteger(self):
#        """
#        @return the single integer that this NestedInteger holds, if it holds a single integer
#        Return None if this NestedInteger holds a nested list
#        :rtype int
#        """
#
#    def getList(self):
#        """
#        @return the nested list that this NestedInteger holds, if it holds a nested list
#        Return None if this NestedInteger holds a single integer
#        :rtype List[NestedInteger]
#        """

class Solution:
    def depthSumInverse(self, nestedList: List[NestedInteger]) -> int:
        def getMaxDepth(nested_list, depth):
            max_depth = depth
            for item in nested_list:
                if not item.isInteger():
                    max_depth = max(max_depth, getMaxDepth(item.getList(), depth + 1))
            return max_depth
        
        max_depth = getMaxDepth(nestedList, 1)
        
        def dfs(nested_list, depth):
            total = 0
            for item in nested_list:
                if item.isInteger():
                    total += item.getInteger() * (max_depth - depth + 1)
                else:
                    total += dfs(item.getList(), depth + 1)
            return total
        
        return dfs(nestedList, 1)