#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        
        int maxSum = nums[0], curMax = nums[0];
        int minSum = nums[0], curMin = nums[0];
        
        for (int i = 1; i < nums.size(); i++) {
            curMax = max(nums[i], curMax + nums[i]);
            maxSum = max(maxSum, curMax);
            curMin = min(nums[i], curMin + nums[i]);
            minSum = min(minSum, curMin);
        }
        
        return total == minSum ? maxSum : max(maxSum, total - minSum);
    }
};
