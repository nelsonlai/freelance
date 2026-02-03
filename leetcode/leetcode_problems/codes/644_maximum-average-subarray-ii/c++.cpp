/*
 * Problem: Maximum Average Subarray II
 * Difficulty: Hard
 * Tags: array, search
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    bool canAchieve(vector<int>& nums, int k, double target) {
        vector<double> prefix(nums.size() + 1, 0);
        double minPrefix = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            prefix[i + 1] = prefix[i] + nums[i] - target;
            if (i >= k - 1) {
                if (prefix[i + 1] >= minPrefix) {
                    return true;
                }
                minPrefix = min(minPrefix, prefix[i - k + 2]);
            }
        }
        
        return false;
    }

public:
    double findMaxAverage(vector<int>& nums, int k) {
        double left = INT_MIN, right = INT_MAX;
        for (int num : nums) {
            left = min(left, (double)num);
            right = max(right, (double)num);
        }
        
        while (right - left > 1e-5) {
            double mid = (left + right) / 2;
            if (canAchieve(nums, k, mid)) {
                left = mid;
            } else {
                right = mid;
            }
        }
        
        return left;
    }
};