/*
 * Problem: Number of Ways of Cutting a Pizza
 * Difficulty: Hard
 * Tags: array, dp
 * 
 * Approach: DP with memoization - dp[r][c][cuts] = ways to cut from (r,c) with cuts remaining
 * Time Complexity: O(rows * cols * k * (rows + cols))
 * Space Complexity: O(rows * cols * k)
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
private:
    int MOD = 1000000007;
    int rows, cols;
    vector<vector<int>> prefix;
    unordered_map<string, long long> memo;
    
    bool hasApple(int r1, int c1, int r2, int c2) {
        return prefix[r1][c1] - prefix[r2][c1] - prefix[r1][c2] + prefix[r2][c2] > 0;
    }
    
    long long dp(int r, int c, int cuts) {
        string key = to_string(r) + "," + to_string(c) + "," + to_string(cuts);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        if (cuts == 0) {
            return hasApple(r, c, rows, cols) ? 1 : 0;
        }
        
        long long result = 0;
        
        for (int i = r + 1; i < rows; i++) {
            if (hasApple(r, c, i, cols)) {
                result = (result + dp(i, c, cuts - 1)) % MOD;
            }
        }
        
        for (int j = c + 1; j < cols; j++) {
            if (hasApple(r, c, rows, j)) {
                result = (result + dp(r, j, cuts - 1)) % MOD;
            }
        }
        
        memo[key] = result;
        return result;
    }

public:
    int ways(vector<string>& pizza, int k) {
        rows = pizza.size();
        cols = pizza[0].length();
        prefix = vector<vector<int>>(rows + 1, vector<int>(cols + 1, 0));
        
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                prefix[i][j] = prefix[i+1][j] + prefix[i][j+1] - prefix[i+1][j+1] +
                               (pizza[i][j] == 'A' ? 1 : 0);
            }
        }
        
        return (int) dp(0, 0, k - 1);
    }
};