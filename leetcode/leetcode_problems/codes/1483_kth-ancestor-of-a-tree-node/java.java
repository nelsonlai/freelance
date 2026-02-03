/**
 * Problem: Kth Ancestor of a Tree Node
 * Difficulty: Hard
 * Tags: array, tree, dp, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

class TreeAncestor {
    private int log;
    private int[][] ancestors;

    public TreeAncestor(int n, int[] parent) {
        this.log = 16;
        this.ancestors = new int[n][log];
        
        for (int i = 0; i < n; i++) {
            ancestors[i][0] = parent[i];
        }
        
        for (int j = 1; j < log; j++) {
            for (int i = 0; i < n; i++) {
                if (ancestors[i][j - 1] != -1) {
                    ancestors[i][j] = ancestors[ancestors[i][j - 1]][j - 1];
                } else {
                    ancestors[i][j] = -1;
                }
            }
        }
    }
    
    public int getKthAncestor(int node, int k) {
        for (int j = 0; j < log; j++) {
            if (((k >> j) & 1) == 1) {
                node = ancestors[node][j];
                if (node == -1) {
                    return -1;
                }
            }
        }
        return node;
    }
}

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor obj = new TreeAncestor(n, parent);
 * int param_1 = obj.getKthAncestor(node,k);
 */