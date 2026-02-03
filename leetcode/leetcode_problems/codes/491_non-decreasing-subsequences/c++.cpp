/*
 * Problem: Non-decreasing Subsequences
 * Difficulty: Medium
 * Tags: array, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <set>

using namespace std;

class Solution {
private:
    void backtrack(int index, vector<int>& nums, vector<int>& sequence, set<vector<int>>& result) {
        if (sequence.size() >= 2) {
            result.insert(sequence);
        }
        
        for (int i = index; i < nums.size(); i++) {
            if (sequence.empty() || nums[i] >= sequence.back()) {
                sequence.push_back(nums[i]);
                backtrack(i + 1, nums, sequence, result);
                sequence.pop_back();
            }
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        set<vector<int>> resultSet;
        vector<int> sequence;
        backtrack(0, nums, sequence, resultSet);
        return vector<vector<int>>(resultSet.begin(), resultSet.end());
    }
};