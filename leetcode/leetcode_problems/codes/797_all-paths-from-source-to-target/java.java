import java.util.*;

class Solution {
    private List<List<Integer>> result;
    
    public List<List<Integer>> allPathsSourceTarget(int[][] graph) {
        result = new ArrayList<>();
        dfs(graph, 0, new ArrayList<>(Arrays.asList(0)));
        return result;
    }
    
    private void dfs(int[][] graph, int node, List<Integer> path) {
        if (node == graph.length - 1) {
            result.add(new ArrayList<>(path));
            return;
        }
        
        for (int neighbor : graph[node]) {
            path.add(neighbor);
            dfs(graph, neighbor, path);
            path.remove(path.size() - 1);
        }
    }
}
