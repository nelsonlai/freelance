/*
 * Problem: Move Zeroes
 * Difficulty: Easy
 * Tags: array
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>

using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int write = 0;
        for (int read = 0; read < nums.size(); read++) {
            if (nums[read] != 0) {
                swap(nums[write], nums[read]);
                write++;
            }
        }
    }
};