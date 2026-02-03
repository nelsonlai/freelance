/*
 * Problem: Minimum Time to Collect All Apples in a Tree
 * Difficulty: Medium
 * Tags: array, tree, hash, search
 * 
 * Approach: DFS - return time needed for subtree, add 2 for each edge to visit
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n) for tree
 */

#include <vector>

using namespace std;

class Solution {
private:
    int dfs(int node, int parent, vector<vector<int>>& tree, vector<bool>& hasApple) {
        int totalTime = 0;
        for (int child : tree[node]) {
            if (child == parent) {
                continue;
            }
            int childTime = dfs(child, node, tree, hasApple);
            if (childTime > 0 || hasApple[child]) {
                totalTime += childTime + 2;
            }
        }
        return totalTime;
    }

public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>> tree(n);
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        return dfs(0, -1, tree, hasApple);
    }
};