import java.util.*;

class Solution {
    private int[][][] memo;
    
    public int catMouseGame(int[][] graph) {
        int n = graph.length;
        memo = new int[2 * n][n][n];
        for (int i = 0; i < 2 * n; i++) {
            for (int j = 0; j < n; j++) {
                Arrays.fill(memo[i][j], -1);
            }
        }
        return dfs(graph, 1, 2, 0);
    }
    
    private int dfs(int[][] graph, int mouse, int cat, int turn) {
        if (turn == 2 * graph.length) {
            return 0;
        }
        if (mouse == 0) {
            return 1;
        }
        if (mouse == cat) {
            return 2;
        }
        if (memo[turn][mouse][cat] != -1) {
            return memo[turn][mouse][cat];
        }
        
        if (turn % 2 == 0) {
            boolean canDraw = false;
            for (int next : graph[mouse]) {
                int result = dfs(graph, next, cat, turn + 1);
                if (result == 1) {
                    return memo[turn][mouse][cat] = 1;
                }
                if (result == 0) {
                    canDraw = true;
                }
            }
            return memo[turn][mouse][cat] = canDraw ? 0 : 2;
        } else {
            boolean canDraw = false;
            for (int next : graph[cat]) {
                if (next == 0) continue;
                int result = dfs(graph, mouse, next, turn + 1);
                if (result == 2) {
                    return memo[turn][mouse][cat] = 2;
                }
                if (result == 0) {
                    canDraw = true;
                }
            }
            return memo[turn][mouse][cat] = canDraw ? 0 : 1;
        }
    }
}
