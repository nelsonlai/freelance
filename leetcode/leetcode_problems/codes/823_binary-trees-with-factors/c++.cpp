#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        int MOD = 1000000007;
        sort(arr.begin(), arr.end());
        unordered_map<int, long> dp;
        for (int num : arr) {
            dp[num] = 1;
        }
        
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (arr[i] % arr[j] == 0) {
                    int factor = arr[i] / arr[j];
                    if (dp.find(factor) != dp.end()) {
                        dp[arr[i]] = (dp[arr[i]] + dp[arr[j]] * dp[factor]) % MOD;
                    }
                }
            }
        }
        
        long result = 0;
        for (auto& entry : dp) {
            result = (result + entry.second) % MOD;
        }
        return (int) result;
    }
};
