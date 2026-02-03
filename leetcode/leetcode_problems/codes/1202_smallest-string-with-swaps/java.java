/**
 * Problem: Smallest String With Swaps
 * Difficulty: Medium
 * Tags: array, string, graph, hash, sort, search
 * 
 * Approach: Union-Find to group connected indices, sort characters in each group
 * Time Complexity: O(n log n) for sorting
 * Space Complexity: O(n) for Union-Find and groups
 */
import java.util.*;

class Solution {
    private int[] parent;
    
    private int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    private void union(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px != py) {
            parent[px] = py;
        }
    }
    
    public String smallestStringWithSwaps(String s, List<List<Integer>> pairs) {
        int n = s.length();
        parent = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (List<Integer> pair : pairs) {
            union(pair.get(0), pair.get(1));
        }
        
        Map<Integer, List<Integer>> groups = new HashMap<>();
        for (int i = 0; i < n; i++) {
            int root = find(i);
            groups.computeIfAbsent(root, k -> new ArrayList<>()).add(i);
        }
        
        char[] result = s.toCharArray();
        for (List<Integer> indices : groups.values()) {
            List<Character> chars = new ArrayList<>();
            for (int idx : indices) {
                chars.add(s.charAt(idx));
            }
            Collections.sort(chars);
            Collections.sort(indices);
            for (int i = 0; i < indices.size(); i++) {
                result[indices.get(i)] = chars.get(i);
            }
        }
        
        return new String(result);
    }
}