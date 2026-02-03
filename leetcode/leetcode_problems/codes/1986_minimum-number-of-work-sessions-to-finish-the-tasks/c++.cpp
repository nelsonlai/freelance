/*
 * Problem: Minimum Number of Work Sessions to Finish the Tasks
 * Difficulty: Medium
 * Tags: array, dp, bitmask
 * 
 * Approach: DP with bitmask - find minimum sessions to complete all tasks
 * Time Complexity: O(n * 2^n) where n is tasks
 * Space Complexity: O(2^n)
 */

#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

class Solution {
private:
    int dp(int mask, vector<int>& tasks, int sessionTime, vector<int>& memo) {
        if (mask == 0) {
            return 0;
        }
        
        if (memo[mask] != -1) {
            return memo[mask];
        }
        
        int result = INT_MAX;
        
        // Try all subsets that fit in one session
        for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
            int total = 0;
            for (int i = 0; i < tasks.size(); i++) {
                if ((submask >> i) & 1) {
                    total += tasks[i];
                }
            }
            
            if (total <= sessionTime) {
                result = min(result, 1 + dp(mask ^ submask, tasks, sessionTime, memo));
            }
        }
        
        memo[mask] = result;
        return result;
    }
    
public:
    int minSessions(vector<int>& tasks, int sessionTime) {
        int n = tasks.size();
        vector<int> memo(1 << n, -1);
        return dp((1 << n) - 1, tasks, sessionTime, memo);
    }
};
