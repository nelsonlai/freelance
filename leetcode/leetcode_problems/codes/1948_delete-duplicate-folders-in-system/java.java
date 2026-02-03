/**
 * Problem: Delete Duplicate Folders in System
 * Difficulty: Hard
 * Tags: array, string, hash, trie, tree serialization
 * 
 * Approach: Build trie, serialize subtrees, mark duplicates, collect non-duplicate paths
 * Time Complexity: O(n * m) where n is paths, m is avg depth
 * Space Complexity: O(n * m)
 */

import java.util.*;

class TrieNode {
    Map<String, TrieNode> children = new HashMap<>();
    int count = 0;
}

class Solution {
    public List<List<String>> deleteDuplicateFolder(List<List<String>> paths) {
        TrieNode root = new TrieNode();
        
        // Build trie
        Collections.sort(paths, (a, b) -> {
            for (int i = 0; i < Math.min(a.size(), b.size()); i++) {
                int cmp = a.get(i).compareTo(b.get(i));
                if (cmp != 0) return cmp;
            }
            return Integer.compare(a.size(), b.size());
        });
        
        for (List<String> path : paths) {
            TrieNode node = root;
            for (String folder : path) {
                node.children.putIfAbsent(folder, new TrieNode());
                node = node.children.get(folder);
            }
        }
        
        // Serialize and count
        Map<String, Integer> serialMap = new HashMap<>();
        serialize(root, serialMap);
        
        // Mark duplicates
        markDuplicates(root, serialMap);
        
        // Collect paths
        List<List<String>> result = new ArrayList<>();
        collect(root, new ArrayList<>(), result);
        
        return result;
    }
    
    private String serialize(TrieNode node, Map<String, Integer> serialMap) {
        if (node.children.isEmpty()) {
            return "";
        }
        
        List<String> parts = new ArrayList<>();
        List<String> sortedKeys = new ArrayList<>(node.children.keySet());
        Collections.sort(sortedKeys);
        
        for (String key : sortedKeys) {
            String childSerial = serialize(node.children.get(key), serialMap);
            parts.add(key + "(" + childSerial + ")");
        }
        
        String serial = String.join(",", parts);
        serialMap.put(serial, serialMap.getOrDefault(serial, 0) + 1);
        return serial;
    }
    
    private String markDuplicates(TrieNode node, Map<String, Integer> serialMap) {
        if (node.children.isEmpty()) {
            return "";
        }
        
        List<String> parts = new ArrayList<>();
        List<String> sortedKeys = new ArrayList<>(node.children.keySet());
        Collections.sort(sortedKeys);
        
        for (String key : sortedKeys) {
            String childSerial = markDuplicates(node.children.get(key), serialMap);
            parts.add(key + "(" + childSerial + ")");
        }
        
        String serial = String.join(",", parts);
        if (serialMap.getOrDefault(serial, 0) > 1) {
            node.count = -1;
        }
        return serial;
    }
    
    private void collect(TrieNode node, List<String> path, List<List<String>> result) {
        if (node.count == -1) {
            return;
        }
        
        if (!path.isEmpty()) {
            result.add(new ArrayList<>(path));
        }
        
        List<String> sortedKeys = new ArrayList<>(node.children.keySet());
        Collections.sort(sortedKeys);
        
        for (String folder : sortedKeys) {
            TrieNode child = node.children.get(folder);
            if (child.count != -1) {
                path.add(folder);
                collect(child, path, result);
                path.remove(path.size() - 1);
            }
        }
    }
}