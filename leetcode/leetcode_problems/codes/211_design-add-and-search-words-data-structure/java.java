/**
 * Problem: Design Add and Search Words Data Structure
 * Difficulty: Medium
 * Tags: string, search
 * 
 * Approach: String manipulation with hash map or two pointers
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

import java.util.*;

class TrieNode {
    Map<Character, TrieNode> children;
    boolean isEnd;
    
    TrieNode() {
        children = new HashMap<>();
        isEnd = false;
    }
}

class WordDictionary {
    private TrieNode root;

    public WordDictionary() {
        root = new TrieNode();
    }
    
    public void addWord(String word) {
        TrieNode node = root;
        for (char c : word.toCharArray()) {
            node.children.putIfAbsent(c, new TrieNode());
            node = node.children.get(c);
        }
        node.isEnd = true;
    }
    
    public boolean search(String word) {
        return searchHelper(root, word, 0);
    }
    
    private boolean searchHelper(TrieNode node, String word, int index) {
        if (index == word.length()) {
            return node.isEnd;
        }
        
        char c = word.charAt(index);
        if (c == '.') {
            for (TrieNode child : node.children.values()) {
                if (searchHelper(child, word, index + 1)) {
                    return true;
                }
            }
            return false;
        } else {
            if (!node.children.containsKey(c)) {
                return false;
            }
            return searchHelper(node.children.get(c), word, index + 1);
        }
    }
}

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * boolean param_2 = obj.search(word);
 */