/*
 * Problem: Stone Game V
 * Difficulty: Hard
 * Tags: array, dp, math
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
    unordered_map<string, int> memo;
    vector<int> prefix;
    
    int dp(int i, int j) {
        if (i >= j) {
            return 0;
        }
        
        string key = to_string(i) + "," + to_string(j);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        int result = 0;
        for (int k = i; k < j; k++) {
            int leftSum = prefix[k + 1] - prefix[i];
            int rightSum = prefix[j + 1] - prefix[k + 1];
            
            if (leftSum < rightSum) {
                result = max(result, leftSum + dp(i, k));
            } else if (leftSum > rightSum) {
                result = max(result, rightSum + dp(k + 1, j));
            } else {
                result = max(result, leftSum + max(dp(i, k), dp(k + 1, j)));
            }
        }
        
        memo[key] = result;
        return result;
    }
    
public:
    int stoneGameV(vector<int>& stoneValue) {
        int n = stoneValue.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stoneValue[i];
        }
        
        memo.clear();
        return dp(0, n - 1);
    }
};