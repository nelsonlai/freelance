/*
 * Problem: Binary Subarrays With Sum
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use prefix sum with hash map to count subarrays with sum equal to goal
 * Time Complexity: O(n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> count;
        count[0] = 1;
        int prefixSum = 0;
        int result = 0;
        
        for (int num : nums) {
            prefixSum += num;
            if (count.find(prefixSum - goal) != count.end()) {
                result += count[prefixSum - goal];
            }
            count[prefixSum]++;
        }
        
        return result;
    }
};