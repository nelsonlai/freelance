/*
 * Problem: Random Pick Index
 * Difficulty: Medium
 * Tags: array, math, hash
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(n) for hash map
 */

#include <vector>
#include <cstdlib>

using namespace std;

class Solution {
private:
    vector<int> nums;

public:
    Solution(vector<int>& nums) {
        this->nums = nums;
    }
    
    int pick(int target) {
        int count = 0;
        int result = -1;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                count++;
                if (rand() % count == 0) {
                    result = i;
                }
            }
        }
        
        return result;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */