/*
 * Problem: Optimal Account Balancing
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    int dfs(int start, vector<int>& debts) {
        while (start < debts.size() && debts[start] == 0) {
            start++;
        }
        if (start == debts.size()) {
            return 0;
        }
        
        int minTransfers = INT_MAX;
        for (int i = start + 1; i < debts.size(); i++) {
            if (debts[start] * debts[i] < 0) {
                debts[i] += debts[start];
                minTransfers = min(minTransfers, 1 + dfs(start + 1, debts));
                debts[i] -= debts[start];
            }
        }
        
        return minTransfers;
    }

public:
    int minTransfers(vector<vector<int>>& transactions) {
        unordered_map<int, int> balance;
        for (auto& t : transactions) {
            balance[t[0]] -= t[2];
            balance[t[1]] += t[2];
        }
        
        vector<int> debts;
        for (auto& entry : balance) {
            if (entry.second != 0) {
                debts.push_back(entry.second);
            }
        }
        
        return dfs(0, debts);
    }
};