/*
 * Problem: Minimum Cost to Connect Two Groups of Points
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

class Solution {
private:
    unordered_map<string, int> memo;
    vector<vector<int>> cost;
    int m, n;
    vector<int> minCostGroup2;
    
    int dp(int i, int mask) {
        if (i == m) {
            int result = 0;
            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j))) {
                    result += minCostGroup2[j];
                }
            }
            return result;
        }
        
        string key = to_string(i) + "," + to_string(mask);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = INT_MAX;
        for (int j = 0; j < n; j++) {
            result = min(result, cost[i][j] + dp(i + 1, mask | (1 << j)));
        }
        
        memo[key] = result;
        return result;
    }
    
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        this->cost = cost;
        this->m = cost.size();
        this->n = cost[0].size();
        
        minCostGroup2.resize(n);
        for (int j = 0; j < n; j++) {
            int minVal = INT_MAX;
            for (int i = 0; i < m; i++) {
                minVal = min(minVal, cost[i][j]);
            }
            minCostGroup2[j] = minVal;
        }
        
        memo.clear();
        return dp(0, 0);
    }
};