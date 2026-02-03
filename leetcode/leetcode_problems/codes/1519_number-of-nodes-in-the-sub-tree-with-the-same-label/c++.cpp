/*
 * Problem: Number of Nodes in the Sub-Tree With the Same Label
 * Difficulty: Medium
 * Tags: array, string, tree, graph, hash, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(h) for recursion stack where h is height
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector<int> dfs(int node, int parent, vector<vector<int>>& tree, string& labels, vector<int>& result) {
        vector<int> count(26, 0);
        count[labels[node] - 'a'] = 1;
        
        for (int child : tree[node]) {
            if (child != parent) {
                vector<int> childCount = dfs(child, node, tree, labels, result);
                for (int i = 0; i < 26; i++) {
                    count[i] += childCount[i];
                }
            }
        }
        
        result[node] = count[labels[node] - 'a'];
        return count;
    }
    
public:
    vector<int> countSubTrees(int n, vector<vector<int>>& edges, string labels) {
        vector<vector<int>> tree(n);
        for (auto& edge : edges) {
            tree[edge[0]].push_back(edge[1]);
            tree[edge[1]].push_back(edge[0]);
        }
        
        vector<int> result(n);
        dfs(0, -1, tree, labels, result);
        return result;
    }
};