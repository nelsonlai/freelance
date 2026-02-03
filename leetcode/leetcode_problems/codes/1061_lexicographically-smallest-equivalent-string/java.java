/**
 * Problem: Lexicographically Smallest Equivalent String
 * Difficulty: Medium
 * Tags: string, graph, sort
 * 
 * Approach: Union-Find to group equivalent characters, assign smallest in each group
 * Time Complexity: O(n * α(n)) where α is inverse Ackermann
 * Space Complexity: O(1) for 26 characters
 */

class Solution {
    public String smallestEquivalentString(String s1, String s2, String baseStr) {
        int[] parent = new int[26];
        for (int i = 0; i < 26; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < s1.length(); i++) {
            union(parent, s1.charAt(i) - 'a', s2.charAt(i) - 'a');
        }
        
        StringBuilder result = new StringBuilder();
        for (char c : baseStr.toCharArray()) {
            result.append((char) (find(parent, c - 'a') + 'a'));
        }
        
        return result.toString();
    }
    
    private int find(int[] parent, int x) {
        if (parent[x] != x) {
            parent[x] = find(parent, parent[x]);
        }
        return parent[x];
    }
    
    private void union(int[] parent, int x, int y) {
        int px = find(parent, x);
        int py = find(parent, y);
        if (px < py) {
            parent[py] = px;
        } else {
            parent[px] = py;
        }
    }
}