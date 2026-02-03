/**
 * Problem: Word Search II
 * Difficulty: Hard
 * Tags: array, string, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class TrieNode {
    Map<Character, TrieNode> children;
    String word;
    
    TrieNode() {
        children = new HashMap<>();
        word = null;
    }
}

class Solution {
    private List<String> result = new ArrayList<>();
    
    public List<String> findWords(char[][] board, String[] words) {
        TrieNode root = new TrieNode();
        for (String word : words) {
            TrieNode node = root;
            for (char c : word.toCharArray()) {
                node.children.putIfAbsent(c, new TrieNode());
                node = node.children.get(c);
            }
            node.word = word;
        }
        
        int m = board.length;
        int n = board[0].length;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (root.children.containsKey(board[i][j])) {
                    dfs(board, i, j, root, m, n);
                }
            }
        }
        
        return result;
    }
    
    private void dfs(char[][] board, int i, int j, TrieNode node, int m, int n) {
        char c = board[i][j];
        TrieNode currNode = node.children.get(c);
        
        if (currNode.word != null) {
            result.add(currNode.word);
            currNode.word = null;
        }
        
        board[i][j] = '#';
        int[][] dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (int[] dir : dirs) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && currNode.children.containsKey(board[ni][nj])) {
                dfs(board, ni, nj, currNode, m, n);
            }
        }
        board[i][j] = c;
        
        if (currNode.children.isEmpty()) {
            node.children.remove(c);
        }
    }
}