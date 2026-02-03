/**
 * Problem: Design Search Autocomplete System
 * Difficulty: Hard
 * Tags: array, string, hash, sort, search, queue, heap
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class TrieNode {
    Map<Character, TrieNode> children;
    Map<String, Integer> sentences;
    
    TrieNode() {
        children = new HashMap<>();
        sentences = new HashMap<>();
    }
}

class AutocompleteSystem {
    private TrieNode root;
    private TrieNode currentNode;
    private StringBuilder currentSentence;

    public AutocompleteSystem(String[] sentences, int[] times) {
        root = new TrieNode();
        currentNode = root;
        currentSentence = new StringBuilder();
        
        for (int i = 0; i < sentences.length; i++) {
            addSentence(sentences[i], times[i]);
        }
    }
    
    private void addSentence(String sentence, int time) {
        TrieNode node = root;
        for (char c : sentence.toCharArray()) {
            node.children.putIfAbsent(c, new TrieNode());
            node = node.children.get(c);
            node.sentences.put(sentence, node.sentences.getOrDefault(sentence, 0) + time);
        }
    }
    
    public List<String> input(char c) {
        if (c == '#') {
            addSentence(currentSentence.toString(), 1);
            currentSentence = new StringBuilder();
            currentNode = root;
            return new ArrayList<>();
        }
        
        currentSentence.append(c);
        if (currentNode != null && currentNode.children.containsKey(c)) {
            currentNode = currentNode.children.get(c);
        } else {
            currentNode = null;
            return new ArrayList<>();
        }
        
        List<Map.Entry<String, Integer>> candidates = new ArrayList<>(currentNode.sentences.entrySet());
        candidates.sort((a, b) -> {
            if (!a.getValue().equals(b.getValue())) {
                return b.getValue() - a.getValue();
            }
            return a.getKey().compareTo(b.getKey());
        });
        
        List<String> result = new ArrayList<>();
        for (int i = 0; i < Math.min(3, candidates.size()); i++) {
            result.add(candidates.get(i).getKey());
        }
        
        return result;
    }
}

/**
 * Your AutocompleteSystem object will be instantiated and called as such:
 * AutocompleteSystem obj = new AutocompleteSystem(sentences, times);
 * List<String> param_1 = obj.input(c);
 */