#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        int MOD = 1000000007;
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<long> pow2(n);
        pow2[0] = 1;
        for (int i = 1; i < n; i++) {
            pow2[i] = pow2[i - 1] * 2 % MOD;
        }
        
        long result = 0;
        for (int i = 0; i < n; i++) {
            result = (result + nums[i] * (pow2[i] - pow2[n - 1 - i])) % MOD;
        }
        return (int)result;
    }
};
