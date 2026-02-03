import java.util.*;

class Solution {
    private List<List<Integer>> graph;
    private int[] quiet;
    private int[] result;
    
    public int[] loudAndRich(int[][] richer, int[] quiet) {
        int n = quiet.length;
        this.quiet = quiet;
        this.result = new int[n];
        Arrays.fill(result, -1);
        
        graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : richer) {
            graph.get(edge[1]).add(edge[0]);
        }
        
        for (int i = 0; i < n; i++) {
            dfs(i);
        }
        return result;
    }
    
    private int dfs(int node) {
        if (result[node] >= 0) {
            return result[node];
        }
        result[node] = node;
        for (int neighbor : graph.get(node)) {
            int candidate = dfs(neighbor);
            if (quiet[candidate] < quiet[result[node]]) {
                result[node] = candidate;
            }
        }
        return result[node];
    }
}
