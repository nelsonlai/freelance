/*
 * Problem: Maximum Number of Non-Overlapping Subarrays With Sum Equals Target
 * Difficulty: Medium
 * Tags: array, greedy, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        unordered_map<int, int> prefixSum;
        prefixSum[0] = -1;
        int currentSum = 0;
        int count = 0;
        int lastEnd = -1;
        
        for (int i = 0; i < nums.size(); i++) {
            currentSum += nums[i];
            if (prefixSum.find(currentSum - target) != prefixSum.end()) {
                int prevIdx = prefixSum[currentSum - target];
                if (prevIdx >= lastEnd) {
                    count++;
                    lastEnd = i;
                }
            }
            prefixSum[currentSum] = i;
        }
        
        return count;
    }
};