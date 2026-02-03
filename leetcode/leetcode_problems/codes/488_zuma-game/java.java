/**
 * Problem: Zuma Game
 * Difficulty: Hard
 * Tags: string, dp, search, stack
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

import java.util.*;

class Solution {
    public int findMinStep(String board, String hand) {
        Map<Character, Integer> handCount = new HashMap<>();
        for (char c : hand.toCharArray()) {
            handCount.put(c, handCount.getOrDefault(c, 0) + 1);
        }
        return dfs(board, handCount);
    }
    
    private int dfs(String board, Map<Character, Integer> hand) {
        if (board.isEmpty()) {
            return 0;
        }
        if (hand.isEmpty()) {
            return -1;
        }
        
        int result = Integer.MAX_VALUE;
        int i = 0;
        while (i < board.length()) {
            int j = i;
            while (j < board.length() && board.charAt(j) == board.charAt(i)) {
                j++;
            }
            
            int need = 3 - (j - i);
            char color = board.charAt(i);
            if (hand.containsKey(color) && hand.get(color) >= need) {
                Map<Character, Integer> newHand = new HashMap<>(hand);
                newHand.put(color, newHand.get(color) - need);
                if (newHand.get(color) == 0) {
                    newHand.remove(color);
                }
                
                String newBoard = removeConsecutive(board.substring(0, i) + board.substring(j));
                int res = dfs(newBoard, newHand);
                if (res != -1) {
                    result = Math.min(result, res + need);
                }
            }
            i = j;
        }
        
        return result == Integer.MAX_VALUE ? -1 : result;
    }
    
    private String removeConsecutive(String s) {
        int i = 0;
        while (i < s.length()) {
            int j = i;
            while (j < s.length() && s.charAt(j) == s.charAt(i)) {
                j++;
            }
            if (j - i >= 3) {
                s = s.substring(0, i) + s.substring(j);
                i = 0;
            } else {
                i = j;
            }
        }
        return s;
    }
}