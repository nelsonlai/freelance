"""
Problem: Mini Parser
Difficulty: Medium
Tags: string, search, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
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
    def deserialize(self, s: str) -> NestedInteger:
        if not s:
            return NestedInteger()
        
        if s[0] != '[':
            return NestedInteger(int(s))
        
        stack = []
        num = None
        negative = False
        
        for i, char in enumerate(s):
            if char == '[':
                stack.append(NestedInteger())
            elif char == '-':
                negative = True
            elif char.isdigit():
                if num is None:
                    num = 0
                num = num * 10 + int(char)
            elif char == ',' or char == ']':
                if num is not None:
                    if negative:
                        num = -num
                    stack[-1].add(NestedInteger(num))
                    num = None
                    negative = False
                
                if char == ']' and len(stack) > 1:
                    nested = stack.pop()
                    stack[-1].add(nested)
        
        return stack[0] if stack else NestedInteger()