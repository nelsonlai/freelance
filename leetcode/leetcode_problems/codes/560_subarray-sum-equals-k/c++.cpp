/*
 * Problem: Subarray Sum Equals K
 * Difficulty: Medium
 * Tags: array, hash
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
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        count[0] = 1;
        int prefixSum = 0;
        int result = 0;
        
        for (int num : nums) {
            prefixSum += num;
            result += count[prefixSum - k];
            count[prefixSum]++;
        }
        
        return result;
    }
};