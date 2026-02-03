/*
 * Problem: Integer Replacement
 * Difficulty: Medium
 * Tags: dp, greedy
 * 
 * Approach: Dynamic programming with memoization or tabulation
 * Time Complexity: O(n * m) where n and m are problem dimensions
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<long, int> memo;
    
    int dfs(long n) {
        if (n == 1) {
            return 0;
        }
        if (memo.find(n) != memo.end()) {
            return memo[n];
        }
        
        int result;
        if (n % 2 == 0) {
            result = 1 + dfs(n / 2);
        } else {
            result = 1 + min(dfs(n + 1), dfs(n - 1));
        }
        
        memo[n] = result;
        return result;
    }

public:
    int integerReplacement(int n) {
        return dfs((long)n);
    }
};