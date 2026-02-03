/*
 * Problem: Paint House II
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        if (costs.empty() || costs[0].empty()) {
            return 0;
        }
        
        int n = costs.size();
        int k = costs[0].size();
        
        for (int i = 1; i < n; i++) {
            int min1 = INT_MAX, min2 = INT_MAX;
            int min1Idx = -1;
            
            for (int j = 0; j < k; j++) {
                if (costs[i - 1][j] < min1) {
                    min2 = min1;
                    min1 = costs[i - 1][j];
                    min1Idx = j;
                } else if (costs[i - 1][j] < min2) {
                    min2 = costs[i - 1][j];
                }
            }
            
            for (int j = 0; j < k; j++) {
                if (j == min1Idx) {
                    costs[i][j] += min2;
                } else {
                    costs[i][j] += min1;
                }
            }
        }
        
        int result = INT_MAX;
        for (int j = 0; j < k; j++) {
            result = min(result, costs[n - 1][j]);
        }
        
        return result;
    }
};