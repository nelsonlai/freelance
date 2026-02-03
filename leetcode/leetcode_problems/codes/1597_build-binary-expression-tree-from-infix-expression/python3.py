"""
Problem: Build Binary Expression Tree From Infix Expression
Difficulty: Hard
Tags: string, tree, stack

Approach: Use shunting yard algorithm or recursive descent parser
Time Complexity: O(n) where n is length of expression
Space Complexity: O(n) for stack
"""

# Definition for a binary tree node.
# class Node(object):
#     def __init__(self, val=" ", left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def expTree(self, s: str) -> 'Node':
        def get_priority(op):
            if op in '+-':
                return 1
            if op in '*/':
                return 2
            return 0
        
        def build_tree(tokens):
            ops = []
            nodes = []
            
            for token in tokens:
                if token.isdigit():
                    nodes.append(Node(token))
                elif token == '(':
                    ops.append(token)
                elif token == ')':
                    while ops and ops[-1] != '(':
                        op = ops.pop()
                        right = nodes.pop()
                        left = nodes.pop()
                        nodes.append(Node(op, left, right))
                    ops.pop()
                else:
                    while ops and ops[-1] != '(' and get_priority(ops[-1]) >= get_priority(token):
                        op = ops.pop()
                        right = nodes.pop()
                        left = nodes.pop()
                        nodes.append(Node(op, left, right))
                    ops.append(token)
            
            while ops:
                op = ops.pop()
                right = nodes.pop()
                left = nodes.pop()
                nodes.append(Node(op, left, right))
            
            return nodes[0]
        
        tokens = []
        i = 0
        while i < len(s):
            if s[i].isdigit():
                num = ''
                while i < len(s) and s[i].isdigit():
                    num += s[i]
                    i += 1
                tokens.append(num)
            else:
                tokens.append(s[i])
                i += 1
        
        return build_tree(tokens)