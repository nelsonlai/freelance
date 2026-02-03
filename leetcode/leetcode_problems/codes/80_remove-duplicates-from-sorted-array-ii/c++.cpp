/*
 * Problem: Remove Duplicates from Sorted Array II
 * Difficulty: Medium
 * Tags: array, sort
 * 
 * Approach: Use two pointers or sliding window technique
 * Time Complexity: O(n) or O(n log n)
 * Space Complexity: O(1) to O(n) depending on approach
 */

#include <vector>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size();
        }
        
        int write = 2;
        for (int read = 2; read < nums.size(); read++) {
            if (nums[read] != nums[write - 2]) {
                nums[write] = nums[read];
                write++;
            }
        }
        
        return write;
    }
};