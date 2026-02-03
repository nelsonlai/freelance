/*
 * Problem: Diagonal Traverse II
 * Difficulty: Medium
 * Tags: array, sort, queue, heap
 * 
 * Approach: Group elements by (row + col), reverse each group, concatenate
 * Time Complexity: O(n) where n is total elements
 * Space Complexity: O(n) for groups
 */

#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        map<int, vector<int>> groups;
        
        for (int i = 0; i < nums.size(); i++) {
            for (int j = 0; j < nums[i].size(); j++) {
                groups[i + j].push_back(nums[i][j]);
            }
        }
        
        vector<int> result;
        for (auto& [key, group] : groups) {
            reverse(group.begin(), group.end());
            result.insert(result.end(), group.begin(), group.end());
        }
        
        return result;
    }
};