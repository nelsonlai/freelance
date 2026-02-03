/*
 * Problem: Count Number of Pairs With Absolute Difference K
 * Difficulty: Easy
 * Tags: array, hash
 * 
 * Approach: Use hash map to count occurrences, check for nums[i] ± k
 * Time Complexity: O(n) where n is length
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countKDifference(vector<int>& nums, int k) {
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        int result = 0;
        for (auto& [num, cnt] : count) {
            if (count.find(num + k) != count.end()) {
                result += cnt * count[num + k];
            }
        }
        
        return result;
    }
};