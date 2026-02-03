/*
 * Problem: Find the Shortest Superstring
 * Difficulty: Hard
 * Tags: array, string, tree, dp
 * 
 * Approach: Traveling Salesman Problem with DP - find optimal order to concatenate words
 * Time Complexity: O(n^2 * (2^n + m)) where n is number of words, m is average word length
 * Space Complexity: O(n * 2^n) for DP table
 */

#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        
        // Calculate overlap between words
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    for (int k = min(words[i].length(), words[j].length()); k > 0; k--) {
                        if (words[i].substr(words[i].length() - k) == words[j].substr(0, k)) {
                            overlap[i][j] = k;
                            break;
                        }
                    }
                }
            }
        }
        
        // DP: dp[mask][i] = maximum overlap ending with word i using mask
        vector<vector<int>> dp(1 << n, vector<int>(n, 0));
        vector<vector<int>> parent(1 << n, vector<int>(n, -1));
        
        for (int mask = 1; mask < (1 << n); mask++) {
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) continue;
                int prevMask = mask ^ (1 << i);
                if (prevMask == 0) continue;
                for (int j = 0; j < n; j++) {
                    if ((prevMask & (1 << j)) != 0) {
                        int val = dp[prevMask][j] + overlap[j][i];
                        if (val > dp[mask][i]) {
                            dp[mask][i] = val;
                            parent[mask][i] = j;
                        }
                    }
                }
            }
        }
        
        // Find best ending word
        int last = 0;
        int maxVal = dp[(1 << n) - 1][0];
        for (int i = 1; i < n; i++) {
            if (dp[(1 << n) - 1][i] > maxVal) {
                maxVal = dp[(1 << n) - 1][i];
                last = i;
            }
        }
        
        // Reconstruct path
        vector<int> path;
        int mask = (1 << n) - 1;
        while (last != -1) {
            path.push_back(last);
            int newMask = mask ^ (1 << last);
            last = parent[mask][last];
            mask = newMask;
        }
        reverse(path.begin(), path.end());
        
        // Build result
        string result = words[path[0]];
        for (int i = 1; i < path.size(); i++) {
            int overlapLen = overlap[path[i-1]][path[i]];
            result += words[path[i]].substr(overlapLen);
        }
        
        return result;
    }
};