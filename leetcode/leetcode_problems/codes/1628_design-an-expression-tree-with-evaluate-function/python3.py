"""
Problem: Design an Expression Tree With Evaluate Function
Difficulty: Medium
Tags: array, tree, math, stack

Approach: Use two pointers or sliding window technique
Time Complexity: O(n) or O(n log n)
Space Complexity: O(h) for recursion stack where h is height
"""

import abc 
from abc import ABC, abstractmethod 
"""
This is the interface for the expression tree Node.
You should not remove it, and you can define some classes to implement it.
"""

class Node(ABC):
    @abstractmethod
    def evaluate(self) -> int:
        pass

class NumNode(Node):
    def __init__(self, val):
        self.val = val
    
    def evaluate(self) -> int:
        return self.val

class OpNode(Node):
    def __init__(self, op, left, right):
        self.op = op
        self.left = left
        self.right = right
    
    def evaluate(self) -> int:
        left_val = self.left.evaluate()
        right_val = self.right.evaluate()
        if self.op == '+':
            return left_val + right_val
        elif self.op == '-':
            return left_val - right_val
        elif self.op == '*':
            return left_val * right_val
        else:  # '/'
            return left_val // right_val

"""    
This is the TreeBuilder class.
You can treat it as the driver code that takes the postinfix input 
and returns the expression tree represnting it as a Node.
"""

class TreeBuilder(object):
    def buildTree(self, postfix: List[str]) -> 'Node':
        stack = []
        for token in postfix:
            if token in '+-*/':
                right = stack.pop()
                left = stack.pop()
                stack.append(OpNode(token, left, right))
            else:
                stack.append(NumNode(int(token)))
        return stack[0]