/*
 * Problem: Contains Duplicate II
 * Difficulty: Easy
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
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> seen;
        for (int i = 0; i < nums.size(); i++) {
            if (seen.find(nums[i]) != seen.end() && i - seen[nums[i]] <= k) {
                return true;
            }
            seen[nums[i]] = i;
        }
        return false;
    }
};