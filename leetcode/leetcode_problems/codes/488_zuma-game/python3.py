"""
Problem: Zuma Game
Difficulty: Hard
Tags: string, dp, search, stack

Approach: String manipulation with hash map or two pointers
Time Complexity: O(n) or O(n log n)
Space Complexity: O(n) or O(n * m) for DP table
"""

from collections import Counter

class Solution:
    def findMinStep(self, board: str, hand: str) -> int:
        def remove_consecutive(s):
            i = 0
            while i < len(s):
                j = i
                while j < len(s) and s[j] == s[i]:
                    j += 1
                if j - i >= 3:
                    s = s[:i] + s[j:]
                    i = 0
                else:
                    i = j
            return s
        
        def dfs(board, hand):
            if not board:
                return 0
            
            if not hand:
                return -1
            
            result = float('inf')
            i = 0
            while i < len(board):
                j = i
                while j < len(board) and board[j] == board[i]:
                    j += 1
                
                need = 3 - (j - i)
                if hand[board[i]] >= need:
                    new_hand = hand.copy()
                    new_hand[board[i]] -= need
                    if new_hand[board[i]] == 0:
                        del new_hand[board[i]]
                    
                    new_board = remove_consecutive(board[:i] + board[j:])
                    res = dfs(new_board, new_hand)
                    if res != -1:
                        result = min(result, res + need)
                
                i = j
            
            return result if result != float('inf') else -1
        
        hand_count = Counter(hand)
        result = dfs(board, hand_count)
        return result if result != float('inf') else -1