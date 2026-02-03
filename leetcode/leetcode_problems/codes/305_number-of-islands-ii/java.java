/**
 * Problem: Number of Islands II
 * Difficulty: Hard
 * Tags: array, graph, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

import java.util.*;

class Solution {
    private Map<String, String> parent = new HashMap<>();
    private Map<String, Integer> rank = new HashMap<>();
    private int count = 0;
    
    public List<Integer> numIslands2(int m, int n, int[][] positions) {
        List<Integer> result = new ArrayList<>();
        
        for (int[] pos : positions) {
            int r = pos[0];
            int c = pos[1];
            String key = r + "," + c;
            
            if (parent.containsKey(key)) {
                result.add(count);
                continue;
            }
            
            parent.put(key, key);
            rank.put(key, 0);
            count++;
            
            int[][] directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
            for (int[] dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                String neighbor = nr + "," + nc;
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && parent.containsKey(neighbor)) {
                    union(key, neighbor);
                }
            }
            
            result.add(count);
        }
        
        return result;
    }
    
    private String find(String x) {
        if (!parent.get(x).equals(x)) {
            parent.put(x, find(parent.get(x)));
        }
        return parent.get(x);
    }
    
    private void union(String x, String y) {
        String px = find(x);
        String py = find(y);
        
        if (px.equals(py)) {
            return;
        }
        
        if (rank.get(px) < rank.get(py)) {
            String temp = px;
            px = py;
            py = temp;
        }
        
        parent.put(py, px);
        if (rank.get(px).equals(rank.get(py))) {
            rank.put(px, rank.get(px) + 1);
        }
        count--;
    }
}