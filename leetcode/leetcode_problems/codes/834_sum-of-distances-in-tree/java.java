import java.util.*;

class Solution {
    private List<List<Integer>> graph;
    private int[] count;
    private int[] ans;
    
    public int[] sumOfDistancesInTree(int n, int[][] edges) {
        graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }
        
        count = new int[n];
        Arrays.fill(count, 1);
        ans = new int[n];
        
        dfs(0, -1);
        dfs2(0, -1);
        return ans;
    }
    
    private void dfs(int node, int parent) {
        for (int child : graph.get(node)) {
            if (child != parent) {
                dfs(child, node);
                count[node] += count[child];
                ans[node] += ans[child] + count[child];
            }
        }
    }
    
    private void dfs2(int node, int parent) {
        for (int child : graph.get(node)) {
            if (child != parent) {
                ans[child] = ans[node] - count[child] + count.length - count[child];
                dfs2(child, node);
            }
        }
    }
}
