/**
 * Problem: Longest Word With All Prefixes
 * Difficulty: Medium
 * Tags: array, string, trie
 * 
 * Approach: Use Trie to check if all prefixes exist
 * Time Complexity: O(n * m) where n is words, m is avg length
 * Space Complexity: O(n * m)
 */

import java.util.*;

class TrieNode {
    Map<Character, TrieNode> children = new HashMap<>();
    boolean isEnd = false;
}

class Solution {
    private String result = "";
    
    public String longestWord(String[] words) {
        TrieNode root = new TrieNode();
        
        for (String word : words) {
            TrieNode node = root;
            for (char c : word.toCharArray()) {
                node.children.putIfAbsent(c, new TrieNode());
                node = node.children.get(c);
            }
            node.isEnd = true;
        }
        
        dfs(root, "");
        return result;
    }
    
    private void dfs(TrieNode node, String path) {
        if (path.length() > result.length() || 
            (path.length() == result.length() && path.compareTo(result) < 0)) {
            result = path;
        }
        
        List<Character> sorted = new ArrayList<>(node.children.keySet());
        Collections.sort(sorted);
        
        for (char c : sorted) {
            TrieNode child = node.children.get(c);
            if (child.isEnd) {
                dfs(child, path + c);
            }
        }
    }
}