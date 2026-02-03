/*
 * Problem: Jump Game VII
 * Difficulty: Medium
 * Tags: array, string, dp, sliding window
 * 
 * Approach: DP with sliding window to track reachable positions
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n)
 */

#include <string>
#include <vector>
#include <deque>

using namespace std;

class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.length();
        if (s[n - 1] == '1') {
            return false;
        }
        
        vector<bool> dp(n, false);
        dp[0] = true;
        deque<int> q;
        q.push_back(0);
        
        for (int i = 1; i < n; i++) {
            while (!q.empty() && q.front() < i - maxJump) {
                q.pop_front();
            }
            
            if (s[i] == '0' && !q.empty() && q.front() <= i - minJump) {
                dp[i] = true;
                q.push_back(i);
            }
        }
        
        return dp[n - 1];
    }
};