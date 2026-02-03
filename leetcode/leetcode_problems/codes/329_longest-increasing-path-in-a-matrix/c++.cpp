/*
 * Problem: Longest Increasing Path in a Matrix
 * Difficulty: Hard
 * Tags: array, graph, dp, sort, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
private:
    vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    unordered_map<string, int> memo;
    
    int dfs(vector<vector<int>>& matrix, int i, int j) {
        string key = to_string(i) + "," + to_string(j);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int maxPath = 1;
        for (auto& dir : directions) {
            int ni = i + dir[0];
            int nj = j + dir[1];
            if (ni >= 0 && ni < matrix.size() && nj >= 0 && nj < matrix[0].size() && 
                matrix[ni][nj] > matrix[i][j]) {
                maxPath = max(maxPath, 1 + dfs(matrix, ni, nj));
            }
        }
        
        memo[key] = maxPath;
        return maxPath;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        
        int result = 0;
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                result = max(result, dfs(matrix, i, j));
            }
        }
        
        return result;
    }
};