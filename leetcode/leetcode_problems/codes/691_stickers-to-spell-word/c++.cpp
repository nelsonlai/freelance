/*
 * Problem: Stickers to Spell Word
 * Difficulty: Hard
 * Tags: array, string, dp, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.length();
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        
        for (int state = 0; state < (1 << n); state++) {
            if (dp[state] == INT_MAX) {
                continue;
            }
            
            for (string sticker : stickers) {
                int nextState = state;
                vector<int> count(26, 0);
                for (char c : sticker) {
                    count[c - 'a']++;
                }
                
                for (int i = 0; i < n; i++) {
                    if (((state >> i) & 1) == 0 && count[target[i] - 'a'] > 0) {
                        nextState |= (1 << i);
                        count[target[i] - 'a']--;
                    }
                }
                
                dp[nextState] = min(dp[nextState], dp[state] + 1);
            }
        }
        
        return dp[(1 << n) - 1] == INT_MAX ? -1 : dp[(1 << n) - 1];
    }
};