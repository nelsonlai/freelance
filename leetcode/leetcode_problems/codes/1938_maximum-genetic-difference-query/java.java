/**
 * Problem: Maximum Genetic Difference Query
 * Difficulty: Hard
 * Tags: array, tree, hash, search, trie, DFS
 * 
 * Approach: Build tree, use Trie to find max XOR for each query path
 * Time Complexity: O(n * 18 + q * 18) where n is nodes, q is queries, 18 is bits
 * Space Complexity: O(n * 18)
 */

import java.util.*;

class TrieNode {
    int count = 0;
    TrieNode[] children = new TrieNode[2];
}

class Solution {
    public int[] maxGeneticDifference(int[] parents, int[][] queries) {
        int n = parents.length;
        int rootIdx = -1;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        
        for (int i = 0; i < n; i++) {
            if (parents[i] == -1) {
                rootIdx = i;
            } else {
                graph.get(parents[i]).add(i);
            }
        }
        
        Map<Integer, List<int[]>> queryMap = new HashMap<>();
        for (int i = 0; i < queries.length; i++) {
            int node = queries[i][0];
            int val = queries[i][1];
            queryMap.computeIfAbsent(node, k -> new ArrayList<>()).add(new int[]{val, i});
        }
        
        int[] result = new int[queries.length];
        TrieNode trie = new TrieNode();
        
        dfs(rootIdx, graph, queryMap, trie, result);
        
        return result;
    }
    
    private void dfs(int node, List<List<Integer>> graph, 
                     Map<Integer, List<int[]>> queryMap, 
                     TrieNode trie, int[] result) {
        add(trie, node);
        
        if (queryMap.containsKey(node)) {
            for (int[] query : queryMap.get(node)) {
                int val = query[0];
                int idx = query[1];
                result[idx] = query(trie, val);
            }
        }
        
        for (int child : graph.get(node)) {
            dfs(child, graph, queryMap, trie, result);
        }
        
        remove(trie, node);
    }
    
    private void add(TrieNode root, int num) {
        TrieNode node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (node.children[bit] == null) {
                node.children[bit] = new TrieNode();
            }
            node = node.children[bit];
            node.count++;
        }
    }
    
    private void remove(TrieNode root, int num) {
        TrieNode node = root;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            node = node.children[bit];
            node.count--;
        }
    }
    
    private int query(TrieNode root, int num) {
        TrieNode node = root;
        int res = 0;
        for (int i = 17; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int target = 1 - bit;
            if (node.children[target] != null && node.children[target].count > 0) {
                res |= (1 << i);
                node = node.children[target];
            } else {
                node = node.children[bit];
            }
        }
        return res;
    }
}