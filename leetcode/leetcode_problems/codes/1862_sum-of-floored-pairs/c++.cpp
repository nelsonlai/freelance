/*
 * Problem: Sum of Floored Pairs
 * Difficulty: Hard
 * Tags: array, math, search, prefix sum
 * 
 * Approach: Count frequency, use prefix sum to count pairs efficiently
 * Time Complexity: O(n + max * log(max)) where max is max value
 * Space Complexity: O(max)
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int sumOfFlooredPairs(vector<int>& nums) {
        const int MOD = 1000000007;
        int maxVal = *max_element(nums.begin(), nums.end());
        
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        vector<long long> prefix(maxVal + 1, 0);
        for (int i = 1; i <= maxVal; i++) {
            prefix[i] = prefix[i - 1] + count[i];
        }
        
        long long result = 0;
        for (auto& [num, freq] : count) {
            for (int multiple = num; multiple <= maxVal; multiple += num) {
                int end = min(multiple + num - 1, maxVal);
                long long cnt = prefix[end] - prefix[multiple - 1];
                result = (result + (multiple / num) * cnt * freq) % MOD;
            }
        }
        
        return result;
    }
};