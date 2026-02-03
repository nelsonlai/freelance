import java.util.*;

class Solution {
    private Set<String> visited;
    private StringBuilder result;
    private int k;
    
    public String crackSafe(int n, int k) {
        this.k = k;
        this.visited = new HashSet<>();
        this.result = new StringBuilder();
        
        String start = "0".repeat(n - 1);
        dfs(start);
        return result.toString() + start;
    }
    
    private void dfs(String node) {
        for (int x = 0; x < k; x++) {
            String neighbor = node + x;
            if (!visited.contains(neighbor)) {
                visited.add(neighbor);
                dfs(neighbor.substring(1));
                result.append(x);
            }
        }
    }
}
