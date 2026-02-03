/*
 * Problem: Maximum Size Subarray Sum Equals k
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> sumMap;
        sumMap[0] = -1;
        int prefixSum = 0;
        int maxLength = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];
            if (sumMap.find(prefixSum - k) != sumMap.end()) {
                maxLength = max(maxLength, i - sumMap[prefixSum - k]);
            }
            if (sumMap.find(prefixSum) == sumMap.end()) {
                sumMap[prefixSum] = i;
            }
        }
        
        return maxLength;
    }
};