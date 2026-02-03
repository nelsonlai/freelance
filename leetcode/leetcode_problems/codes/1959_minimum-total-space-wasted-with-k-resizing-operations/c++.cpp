/*
 * Problem: Minimum Total Space Wasted With K Resizing Operations
 * Difficulty: Medium
 * Tags: array, dp
 * 
 * Approach: DP - dp[i][j] = min waste using j resizes for first i elements
 * Time Complexity: O(n^2 * k) where n is length
 * Space Complexity: O(n * k)
 */

#include <vector>
#include <climits>
#include <cstring>

using namespace std;

class Solution {
private:
    int waste(int i, int j, vector<int>& nums, vector<vector<int>>& memo) {
        int n = nums.size();
        if (i == n) {
            return 0;
        }
        if (j == 0) {
            int maxVal = 0;
            int sum = 0;
            for (int k = i; k < n; k++) {
                maxVal = max(maxVal, nums[k]);
                sum += nums[k];
            }
            return maxVal * (n - i) - sum;
        }
        
        if (memo[i][j] != -1) {
            return memo[i][j];
        }
        
        int result = INT_MAX;
        int maxVal = 0;
        int sum = 0;
        
        for (int start = i; start < n; start++) {
            maxVal = max(maxVal, nums[start]);
            sum += nums[start];
            int wasteVal = maxVal * (start - i + 1) - sum;
            result = min(result, waste(start + 1, j - 1, nums, memo) + wasteVal);
        }
        
        memo[i][j] = result;
        return result;
    }
    
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> memo(n + 1, vector<int>(k + 1, -1));
        return waste(0, k, nums, memo);
    }
};