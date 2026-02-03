/*
 * Problem: Jump Game
 * Difficulty: Medium
 * Tags: array, dp, greedy
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) or O(n * m) for DP table
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int farthest = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > farthest) {
                return false;
            }
            farthest = max(farthest, i + nums[i]);
            if (farthest >= nums.size() - 1) {
                return true;
            }
        }
        return true;
    }
};