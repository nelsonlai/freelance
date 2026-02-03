/*
 * Problem: Partition Array Into Two Arrays to Minimize Sum Difference
 * Difficulty: Hard
 * Tags: array, dp, search, meet-in-middle
 * 
 * Approach: Meet-in-middle - split array in half, find all possible sums for each half
 * Time Complexity: O(n * 2^(n/2))
 * Space Complexity: O(2^(n/2))
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDifference(vector<int>& nums) {
        int n = nums.size();
        int total = 0;
        for (int num : nums) {
            total += num;
        }
        int target = total / 2;
        
        // Split array in half
        vector<int> left(nums.begin(), nums.begin() + n / 2);
        vector<int> right(nums.begin() + n / 2, nums.end());
        
        // Generate all possible sums for left half with different sizes
        unordered_map<int, vector<int>> leftSums;
        for (int mask = 0; mask < (1 << left.size()); mask++) {
            int sum = 0;
            for (int i = 0; i < left.size(); i++) {
                if (mask & (1 << i)) {
                    sum += left[i];
                }
            }
            int count = __builtin_popcount(mask);
            leftSums[count].push_back(sum);
        }
        
        // Sort for binary search
        for (auto& [count, arr] : leftSums) {
            sort(arr.begin(), arr.end());
        }
        
        // Generate all possible sums for right half
        int result = INT_MAX;
        for (int mask = 0; mask < (1 << right.size()); mask++) {
            int sum = 0;
            for (int i = 0; i < right.size(); i++) {
                if (mask & (1 << i)) {
                    sum += right[i];
                }
            }
            int count = __builtin_popcount(mask);
            int neededCount = n / 2 - count;
            
            if (leftSums.count(neededCount)) {
                vector<int>& arr = leftSums[neededCount];
                // Binary search for closest sum to target - sum
                int idx = lower_bound(arr.begin(), arr.end(), target - sum) - arr.begin();
                
                // Check closest values
                for (int i = max(0, idx - 1); i <= min((int)arr.size() - 1, idx + 1); i++) {
                    int sum1 = sum + arr[i];
                    int sum2 = total - sum1;
                    result = min(result, abs(sum1 - sum2));
                }
            }
        }
        
        return result;
    }
};