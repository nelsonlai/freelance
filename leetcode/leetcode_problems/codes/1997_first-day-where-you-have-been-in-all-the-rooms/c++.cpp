/*
 * Problem: First Day Where You Have Been in All the Rooms
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - dp[i] = days to reach room i for first time
 * Time Complexity: O(n) where n is rooms
 * Space Complexity: O(n)
 */

#include <vector>

using namespace std;

class Solution {
private:
    static constexpr int MOD = 1000000007;
    
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        int n = nextVisit.size();
        vector<long long> dp(n, 0);
        
        for (int i = 1; i < n; i++) {
            // To reach room i, need to:
            // 1. Reach room i-1: dp[i-1] days
            // 2. Visit nextVisit[i-1] and come back: 2 * dp[nextVisit[i-1]] days
            // 3. One more day to reach room i
            dp[i] = (dp[i-1] + 2 * dp[nextVisit[i-1]] + 2) % MOD;
        }
        
        return dp[n-1];
    }
};