/*
 * Problem: Subsets II
 * Difficulty: Medium
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> currentSubset;
        backtrack(result, currentSubset, nums, 0);
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& currentSubset, vector<int>& nums, int start) {
        result.push_back(currentSubset);
        
        for (int i = start; i < nums.size(); i++) {
            if (i > start && nums[i] == nums[i - 1]) {
                continue;
            }
            currentSubset.push_back(nums[i]);
            backtrack(result, currentSubset, nums, i + 1);
            currentSubset.pop_back();
        }
    }
};