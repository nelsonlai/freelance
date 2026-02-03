/*
 * Problem: Shuffle an Array
 * Difficulty: Medium
 * Tags: array, math
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

class Solution {
private:
    vector<int> original;
    vector<int> nums;

public:
    Solution(vector<int>& nums) {
        this->original = nums;
        this->nums = nums;
    }
    
    vector<int> reset() {
        nums = original;
        return nums;
    }
    
    vector<int> shuffle() {
        for (int i = nums.size() - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(nums[i], nums[j]);
        }
        return nums;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */