#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int, int> count;
        int maxNum = 0;
        for (int num : nums) {
            count[num]++;
            maxNum = max(maxNum, num);
        }
        
        vector<int> dp(maxNum + 1, 0);
        dp[1] = count[1];
        
        for (int i = 2; i <= maxNum; i++) {
            dp[i] = max(dp[i - 1], dp[i - 2] + i * count[i]);
        }
        
        return dp[maxNum];
    }
};
