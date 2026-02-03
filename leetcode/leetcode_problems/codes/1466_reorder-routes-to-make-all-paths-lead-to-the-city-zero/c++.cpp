/*
 * Problem: Reorder Routes to Make All Paths Lead to the City Zero
 * Difficulty: Medium
 * Tags: tree, graph, search
 * 
 * Approach: DFS or BFS traversal
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(h) for recursion stack where h is height
 */

class Solution {
public:
    int minReorder(int n, vector<vector<int>>& connections) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto& conn : connections) {
            int u = conn[0], v = conn[1];
            graph[u].push_back({v, 1}); // original direction
            graph[v].push_back({u, 0}); // reversed direction
        }
        
        return dfs(0, -1, graph);
    }
    
private:
    int dfs(int node, int parent, vector<vector<pair<int, int>>>& graph) {
        int count = 0;
        for (auto& [next, isOriginal] : graph[node]) {
            if (next != parent) {
                if (isOriginal == 1) {
                    count++;
                }
                count += dfs(next, node, graph);
            }
        }
        return count;
    }
};