/*
 * Problem: Permutations II
 * Difficulty: Medium
 * Tags: array, sort
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
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(result, current, nums, used);
        return result;
    }
    
private:
    void backtrack(vector<vector<int>>& result, vector<int>& current, 
                   vector<int>& nums, vector<bool>& used) {
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1])) {
                continue;
            }
            used[i] = true;
            current.push_back(nums[i]);
            backtrack(result, current, nums, used);
            current.pop_back();
            used[i] = false;
        }
    }
};