import java.util.*;

class Solution {
    private Map<Integer, List<Integer>> graph;
    private Map<Integer, Integer> color;
    
    public boolean possibleBipartition(int n, int[][] dislikes) {
        graph = new HashMap<>();
        for (int[] dislike : dislikes) {
            graph.computeIfAbsent(dislike[0], k -> new ArrayList<>()).add(dislike[1]);
            graph.computeIfAbsent(dislike[1], k -> new ArrayList<>()).add(dislike[0]);
        }
        
        color = new HashMap<>();
        
        for (int i = 1; i <= n; i++) {
            if (!color.containsKey(i)) {
                if (!dfs(i, 0)) {
                    return false;
                }
            }
        }
        return true;
    }
    
    private boolean dfs(int node, int c) {
        if (color.containsKey(node)) {
            return color.get(node) == c;
        }
        color.put(node, c);
        for (int neighbor : graph.getOrDefault(node, Collections.emptyList())) {
            if (!dfs(neighbor, 1 - c)) {
                return false;
            }
        }
        return true;
    }
}
