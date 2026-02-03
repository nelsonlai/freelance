/*
 * Problem: Count Nodes With the Highest Score
 * Difficulty: Medium
 * Tags: array, tree, search, DFS
 * 
 * Approach: Build tree, calculate subtree sizes, compute scores for each node
 * Time Complexity: O(n) where n is number of nodes
 * Space Complexity: O(n)
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    int dfs(int node, vector<vector<int>>& children, vector<int>& subtreeSize) {
        int size = 1;
        for (int child : children[node]) {
            size += dfs(child, children, subtreeSize);
        }
        subtreeSize[node] = size;
        return size;
    }
    
public:
    int countHighestScoreNodes(vector<int>& parents) {
        int n = parents.size();
        vector<vector<int>> children(n);
        
        // Build tree
        for (int i = 1; i < n; i++) {
            children[parents[i]].push_back(i);
        }
        
        // Calculate subtree sizes
        vector<int> subtreeSize(n);
        dfs(0, children, subtreeSize);
        
        // Calculate scores
        long long maxScore = 0;
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            long long score = 1;
            long long remaining = n - 1;
            
            for (int child : children[i]) {
                score *= subtreeSize[child];
                remaining -= subtreeSize[child];
            }
            
            if (remaining > 0) {
                score *= remaining;
            }
            
            if (score > maxScore) {
                maxScore = score;
                count = 1;
            } else if (score == maxScore) {
                count++;
            }
        }
        
        return count;
    }
};