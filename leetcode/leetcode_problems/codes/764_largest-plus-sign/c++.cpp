#include <vector>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        unordered_set<string> banned;
        for (auto& mine : mines) {
            banned.insert(to_string(mine[0]) + "," + to_string(mine[1]));
        }
        
        vector<vector<int>> dp(n, vector<int>(n, n));
        
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                count = banned.find(to_string(i) + "," + to_string(j)) != banned.end() ? 0 : count + 1;
                dp[i][j] = min(dp[i][j], count);
            }
            
            count = 0;
            for (int j = n - 1; j >= 0; j--) {
                count = banned.find(to_string(i) + "," + to_string(j)) != banned.end() ? 0 : count + 1;
                dp[i][j] = min(dp[i][j], count);
            }
        }
        
        for (int j = 0; j < n; j++) {
            int count = 0;
            for (int i = 0; i < n; i++) {
                count = banned.find(to_string(i) + "," + to_string(j)) != banned.end() ? 0 : count + 1;
                dp[i][j] = min(dp[i][j], count);
            }
            
            count = 0;
            for (int i = n - 1; i >= 0; i--) {
                count = banned.find(to_string(i) + "," + to_string(j)) != banned.end() ? 0 : count + 1;
                dp[i][j] = min(dp[i][j], count);
            }
        }
        
        int result = 0;
        for (auto& row : dp) {
            for (int val : row) {
                result = max(result, val);
            }
        }
        return result;
    }
};
