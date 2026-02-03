/*
 * Problem: Continuous Subarray Sum
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> remainderMap;
        remainderMap[0] = -1;
        int prefixSum = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            prefixSum += nums[i];
            int remainder = prefixSum % k;
            
            if (remainderMap.find(remainder) != remainderMap.end()) {
                if (i - remainderMap[remainder] >= 2) {
                    return true;
                }
            } else {
                remainderMap[remainder] = i;
            }
        }
        
        return false;
    }
};