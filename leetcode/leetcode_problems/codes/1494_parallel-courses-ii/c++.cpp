/*
 * Problem: Parallel Courses II
 * Difficulty: Hard
 * Tags: array, graph, dp
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
private:
    void generateSubsets(vector<int>& arr, int k, int start, vector<int>& current, int mask, vector<int>& dp) {
        if (current.size() == k || start == arr.size()) {
            if (!current.empty()) {
                int newMask = mask;
                for (int course : current) {
                    newMask |= 1 << course;
                }
                dp[newMask] = min(dp[newMask], dp[mask] + 1);
            }
            return;
        }
        
        for (int i = start; i < arr.size(); i++) {
            current.push_back(arr[i]);
            generateSubsets(arr, k, i + 1, current, mask, dp);
            current.pop_back();
        }
    }
    
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
        vector<int> prerequisites(n, 0);
        for (auto& relation : relations) {
            int u = relation[0] - 1;
            int v = relation[1] - 1;
            prerequisites[v] |= 1 << u;
        }
        
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] == INT_MAX) {
                continue;
            }
            
            vector<int> available;
            for (int i = 0; i < n; i++) {
                if (((mask >> i) & 1) == 0 && (prerequisites[i] & mask) == prerequisites[i]) {
                    available.push_back(i);
                }
            }
            
            vector<int> current;
            generateSubsets(available, k, 0, current, mask, dp);
        }
        
        return dp[(1 << n) - 1];
    }
};